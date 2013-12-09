<?php

/*
 * @file
 * Migration for players
 */

class SchemaxSportsMigrationPlayer extends SchemaxSportsMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/LBSC_BCSA_players.csv';

    $this->description = t('Import players into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'player_id' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
        'description' => 'Player ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('schemax_person');

    $this->addFieldMapping('field_schemax_first_name', 'player_first_name');
    $this->addFieldMapping('field_schemax_last_name', 'player_last_name');
    $this->addFieldMapping('field_schemax_gender', 'player_gender');


    $arguments = DateMigrateFieldHandler::arguments('America/Vancouver');
    $this->addFieldMapping('field_schemax_date_of_birth', 'player_date_of_birth')
        ->callbacks(array($this, 'transform_date'))
        ->arguments($arguments);

    $this->addFieldMapping('field_team_id', 'team_id')
        ->sourceMigration('TeamNode');
    $this->addFieldMapping('og_group_ref', 'team_id')
        ->sourceMigration('TeamNode');



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

    $columns[0] = array('district_code', 'District Code');
    $columns[1] = array('club_code', 'Club Code');
    $columns[2] = array('team_id', 'Team ID');
    $columns[3] = array('player_first_name', 'Player First Name');
    $columns[4] = array('player_middle_name', 'Player Middle Name');
    $columns[5] = array('player_last_name', 'Player Last Name');
    $columns[6] = array('player_date_of_birth', 'Player Date of Birth');
    $columns[7] = array('age_group', 'Age Group');
    $columns[8] = array('player_gender', 'Player Gender');
    $columns[9] = array('player_phone_home', 'Player Phone Home');
    $columns[10] = array('player_address_street', 'Player Address Street');
    $columns[11] = array('player_address_postal_code', 'Player Address Postal Code');
    $columns[12] = array('player_address_city', 'Player Address City');
    $columns[13] = array('player_address_province', 'Player Address Province');
    $columns[14] = array('player_email', 'Player Email');
    $columns[15] = array('player_id', 'Player ID');
    $columns[16] = array('player_ood', 'OOD');
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
    $date = DateTime::createFromFormat('!d-m-Y', $value);

    $value = $date->format('Y-m-d h:i:s');

    return $value;
  }

}
