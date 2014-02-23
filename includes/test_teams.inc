<?php

/*
 * @file
 * Migration for teams
 */

class SchemaxMigrationSportsTestTeams extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/xls/league.xls';
    $this->description = t('Import teams into the database');
    $this->source = new MigrateSourceSpreadsheet($source_file_path,'Teams');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'TEAM ID' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Team ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('schemax_team');

    $this->addFieldMapping('title', 'NAME');
    //$this->addFieldMapping('field_schemax_team_id','ID#');
    $this->addFieldMapping('field_schemax_league','League');
    $this->addFieldMapping('field_schemax_club','Club');
    $this->addFieldMapping('field_schemax_district','District');
    $this->addFieldMapping('field_schemax_age_group','AGE LEVEL');
    $this->addFieldMapping('field_schemax_max_players','MAX PLAYERS');



    // Map Team IDs 1:1 to uids from Users migration
    $this->addFieldMapping('uid','TEAM ID')
            ->sourceMigration('Users');


    $this->addFieldMapping('group_access')
            ->defaultValue(0);// 0=public, 1=private

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
      'group_content_access'
    ));
  }

  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    return TRUE;
  }

}
