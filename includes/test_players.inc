<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationSportsTestPlayers extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/xls/league.xls';

    $this->description = t('Import players into the database');
    $this->source = new MigrateSourceSpreadsheet($source_file_path,'Registered Players');

   // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'ID#' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
        'description' => 'Player ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('schemax_person');

    $this->addFieldMapping('field_schemax_player_id','ID#');
    $this->addFieldMapping('og_group_ref', 'TEAM ID')
        ->sourceMigration('TestTeams');

    $this->addFieldMapping('field_schemax_first_name', 'FIRST NAME');
    $this->addFieldMapping('field_schemax_middle_name', 'MIDDLE NAME');
    $this->addFieldMapping('field_schemax_last_name', 'LAST NAME');

    // No need to apply date correction since dates are imported in local time
    //$arguments = DateMigrateFieldHandler::arguments('America/Vancouver');
    $this->addFieldMapping('field_schemax_date_of_birth', 'BIRTH DATE (dd-mm-yyyy)');
    //    ->callbacks(array($this, 'transform_date'))
    //    ->arguments($arguments);

    $this->addFieldMapping('field_schemax_gender', 'GENDER (M/F)');
    $this->addFieldMapping('field_schemax_phone', 'HOME PHONE');

    $this->addFieldMapping('field_schemax_address')
        ->defaultValue('CA');

    $this->addFieldMapping('field_schemax_address:thoroughfare', 'ADDRESS');
    $this->addFieldMapping('field_schemax_address:locality', 'CITY');
    $this->addFieldMapping('field_schemax_address:postal_code', 'POSTAL CODE');
    $this->addFieldMapping('field_schemax_address:administrative_area', 'PROVINCE');

    $this->addFieldMapping('field_schemax_email', 'EMAIL');

    $this->addFieldMapping('field_schemax_team_roles')
        ->defaultValue('Player');

    $this->addFieldMapping('title')
        ->description(t('Node titles for Person bundles are created with automatic entity labels'))
        ->issueGroup(t('DNM'));

        // Map Team IDs 1:1 to uids from Users migration
    $this->addFieldMapping('uid','TEAM ID')
            ->sourceMigration('Users');

    $this->addUnmigratedDestinations(array(
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

  public function transform_date($value) {

    // Source field is in format DD-MM-YYYY.
    // We need to convert to YYYY-MM-DD.
    $date = DateTime::createFromFormat('!d-m-Y', $value);

    $value = $date->format('Y-m-d h:i:s');

    return $value;
  }

}