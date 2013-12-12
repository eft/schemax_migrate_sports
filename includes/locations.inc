<?php

/*
 * @file
 * Migration for players
 */

class SchemaxSportsMigrationLocations extends SchemaxSportsMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/locations.csv';

    $this->description = t('Import locations into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'location_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Location ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNode('schemax_location');

    $this->addFieldMapping(NULL, 'location_id');
    $this->addFieldMapping('title', 'location');
    $this->addFieldMapping('field_schemax_playing_surfaces', 'playing_surface')
        ->sourceMigration('PlayingSurfaces');
    $this->addFieldMapping('field_schemax_location_types', 'location_type')
        ->sourceMigration('LocationTypes');

    $this->addUnmigratedDestinations(array(
      'uid',
      'created',
      'changed',
      'status',
      'promote',
      'sticky',
      'revision',
      'log',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'path',
      'comment',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('location_id', 'Location ID');
    $columns[1] = array('location', 'Location');
    $columns[2] = array('playing_surface', 'Playing Surface');
    $columns[3] = array('location_type', 'Location Type');
    return $columns;
  }

  // Define fields
  protected function fields() {
    // use empty array by default
    return array();
  }

  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    //$row->player_date_of_birth = $row->player_date_of_birth . '-01-02 00:00:00';

    return TRUE;
  }

}
