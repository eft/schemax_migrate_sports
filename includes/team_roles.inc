<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationSportsTeamRoles extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/team_roles.csv';

    $this->description = t('Import team_roles into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'team_roles' => array('type' => 'varchar',
                           'length' => 255,
                           'not null' => TRUE,
                           'description' => 'Team Role',
                          )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    $this->destination = new MigrateDestinationTerm('team_roles');

    $this->addFieldMapping('name', 'team_roles');

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

    $columns[0] = array('team_roles', 'Team Roles');
    return $columns;
  }
}
