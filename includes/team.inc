<?php

/*
 * @file
 * Migration for teams
 */

class SchemaxSportsMigrationTeam extends SchemaxSportsMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/team.csv';

    $this->description = t('Import teams into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'team_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Team ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('schemax_team');

    $this->addFieldMapping('field_schemax_first_name', 'team_first_name');
    $this->addFieldMapping('field_schemax_last_name', 'team_last_name');
    $this->addFieldMapping('field_schemax_gender', 'team_gender');
    $arguments = DateMigrateFieldHandler::arguments('America/Vancouver');
    $this->addFieldMapping('field_schemax_date_of_birth', 'team_date_of_birth')
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
    $columns[4] = array('team_gender', 'Team Gender');
    $columns[5] = array('team_first_name', 'Team First Name');
    $columns[6] = array('team_last_name', 'Team Last Name');
    $columns[7] = array('team_date_of_birth', 'Team Date of Birth');
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
    $row->team_date_of_birth = $row->player_date_of_birth . '-01-02 00:00:00';

    return TRUE;
  }

}
