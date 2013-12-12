<?php

/*
 * @file
 * Migration for players
 */

class SchemaxSportsMigrationLocationTypes extends SchemaxSportsMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/location_types.csv';

    $this->description = t('Import location_types into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'location_types' => array('type' => 'varchar',
                           'length' => 255,
                           'not null' => TRUE,
                           'description' => 'Location Type',
                          )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    $this->destination = new MigrateDestinationTerm('location_types');

    $this->addFieldMapping('name', 'location_types');

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

    $columns[0] = array('location_types', 'Location Types');
    return $columns;
  }
}
