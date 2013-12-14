<?php

/*
 * @file
 * Migration for players
 */

class SchemaxSportsMigrationStaff2 extends SchemaxSportsMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/xls/LBSC_BCSA.xls';
    $this->description = t('test : Import staff teams into the database');
    $this->source = new MigrateSourceSpreadsheet($source_file_path,'Team Staff');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'ID#' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
        'description' => 'Player ID',
      ),
      'TEAM ID' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Team ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('schemax_person');

    $this->systemOfRecord = Migration::DESTINATION;

    // Mapped fields
    // The destination handler needs the nid to change - since the incoming data
    // has a source id, not a nid, we need to apply the original wine migration
    // mapping to populate the nid.
    $this->addFieldMapping('nid','ID#')
         ->sourceMigration('Staff1');



    $this->addFieldMapping('og_group_ref', 'TEAM ID')
        ->sourceMigration('Teams');


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

  public function prepare($entity, $row) {
    $old_node = node_load($entity->nid);
    if (!empty($old_node->og_group_ref)) {
      $entity->og_group_ref['und'] = array_merge($old_node->og_group_ref['und'], $entity->og_group_ref['und']);
    }
  }

}
