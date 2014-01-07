<?php

/*
 * @file
 * Migration for teams
 */

class SchemaxMigrationSportsTestPlayers extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/xls/league.xls';

    $this->description = t('Import teams into the database');
    //$this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), $this->fields());
    $this->source = new MigrateSourceSpreadsheet($source_file_path,'Players');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'PlayerID' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Player ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('schemax_person');

    $this->addFieldMapping('field_team_id','TeamID')
        ->sourceMigration('Teams');

    $this->addFieldMapping('og_group_ref', 'TeamID')
        ->sourceMigration('Teams');

    $this->addFieldMapping('field_player_id','PlayerID');
    $this->addFieldMapping('field_schemax_first_name', 'PlayerName');


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
    //$row->team_date_of_birth = $row->player_date_of_birth . '-01-02 00:00:00';

    return TRUE;
  }

}
