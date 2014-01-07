<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationSportsPlayingSurfaces extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/playing_surfaces.csv';

    $this->description = t('Import playing_surfaces into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'playing_surfaces' => array('type' => 'varchar',
                           'length' => 255,
                           'not null' => TRUE,
                           'description' => 'Playing Surface',
                          )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    $this->destination = new MigrateDestinationTerm('playing_surfaces');

    $this->addFieldMapping('name', 'playing_surfaces');

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

    $columns[0] = array('playing_surfaces', 'Playing Surfaces');
    return $columns;
  }
}
