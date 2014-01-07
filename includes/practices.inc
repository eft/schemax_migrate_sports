<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationSportsPractices extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/practices.csv';

    $this->description = t('Import practices into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'practice_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Practice ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNode('schemax_event');

    $this->addFieldMapping(NULL, 'practice_id');

    $this->addFieldMapping('title', 'practice_name');
    $this->addFieldMapping('field_schemax_location_reference', 'location_id')
        ->sourceMigration('Locations');

    $this->addFieldMapping('og_group_ref', 'team_id')
        ->sourceMigration('Teams');

    // No need to apply date correction since dates are imported in local time
    //$arguments = DateMigrateFieldHandler::arguments('America/Vancouver');
    $this->addFieldMapping('field_date', 'field_date');
    //    ->callbacks(array($this, 'transform_date'));
    //    ->arguments($arguments);

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

    $columns[0] = array('practice_id', 'ID');
    $columns[1] = array('practice_name', 'Practice Name');
    $columns[2] = array('field_date', 'Date');
    $columns[3] = array('team_id', 'TeamID');
    $columns[4] = array('location_id', 'LocationID');
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


  public function transform_date($value) {

    // Source field is in format DD-MM-YYYY.
    // We need to convert to YYYY-MM-DD.
//    $date = DateTime::createFromFormat('!Y-m-d', $value);

//    $value = $date->format('Y-m-d h:i:s');

    return $value;
  }

}
