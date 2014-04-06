<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationSportsEventTypes extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/event_types.csv';

    $this->description = t('Import event types into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'event_types' => array('type' => 'varchar',
                           'length' => 255,
                           'not null' => TRUE,
                           'description' => 'Event Types',
                          )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    $this->destination = new MigrateDestinationTerm('event_types');

    $this->addFieldMapping('name', 'event_types');

    $this->addUnmigratedDestinations(array(
      'tid',
      'description',
      'parent',
      'parent_name',
      'format',
      'weight',
      'path',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('event_types', 'Event Types');
    return $columns;
  }
}
