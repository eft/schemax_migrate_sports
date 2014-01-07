<?php

/*
 * @file
 * Migration for teams
 */

class SchemaxMigrationSportsTeams extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/xls/LBSC_BCSA.xls';
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
    $this->addFieldMapping('field_schemax_team_id','TEAM ID');
    $this->addFieldMapping('field_schemax_league','League');
    $this->addFieldMapping('field_schemax_club','Club');
    $this->addFieldMapping('field_schemax_district','District');
    $this->addFieldMapping('field_schemax_age_group','AGE LEVEL');
    $this->addFieldMapping('field_schemax_max_players','MAX PLAYERS');

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

  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    return TRUE;
  }

}
