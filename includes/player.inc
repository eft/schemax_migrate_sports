<?php

/*
 * @file
 * Migration for players
 */

class SchemaxSportsMigrationPlayer extends SchemaxSportsMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/test.csv';

    $this->description = t('Import players into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'registration_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Registration ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('schemax_person');

    $this->addFieldMapping('field_schemax_first_name', 'player_first_name');
    $this->addFieldMapping('field_schemax_last_name', 'player_last_name');
    $this->addFieldMapping('field_schemax_gender', 'player_gender');
    $arguments = DateMigrateFieldHandler::arguments('America/Vancouver');
    $this->addFieldMapping('field_schemax_date_of_birth', 'player_date_of_birth')
        ->arguments($arguments);

    $this->addFieldMapping('title')
        ->description(t('Node titles for Person bundles are created with automatic entity labels'))
        ->issueGroup(t('DNM'));

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
      'field_schemax_first_name:language',
      'field_schemax_last_name:language',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {
    // Reg_ID	Reg Date	Team	Div	G	First Name	Last Name	Born
    $columns[0] = array('registration_id', 'Registration ID');
    $columns[1] = array('registration_date', 'Registration Date');
    $columns[2] = array('team_name', 'Team Name');
    $columns[3] = array('team_division', 'Team Division');
    $columns[4] = array('player_gender', 'Player Gender');
    $columns[5] = array('player_first_name', 'Player First Name');
    $columns[6] = array('player_last_name', 'Player Last Name');
    $columns[7] = array('player_date_of_birth', 'Player Date of Birth');
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
    $row->player_date_of_birth = $row->player_date_of_birth . '-01-02 00:00:00';

    return TRUE;
  }

}
