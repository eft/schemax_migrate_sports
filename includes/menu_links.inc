<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationSportsMenuLinks extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/menu_links.csv';

    $this->description = t('Import menu-links into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'mlid' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Menu Link ID',
      ),
        ), MigrateDestinationMenuLinks::getKeySchema()
    );

    $this->destination = new MigrateDestinationMenuLinks();

    $this->addFieldMapping('menu_name')->defaultValue('schemax-sports-menu');
    $this->addFieldMapping('mlid', 'mlid');
    $this->addFieldMapping('plid', 'ref_parent')->sourceMigration($this->getMachineName());
    $this->addFieldMapping('link_path', 'link_path');
    $this->addFieldMapping('router_path')->defaultValue('node/%');// default routing for a node
    $this->addFieldMapping('link_title', 'link_title');
    $this->addFieldMapping('weight', 'weight');

    $this->addUnmigratedDestinations(array(
      'options' ,
      'module' ,
      'hidden' ,
      'external' ,
      'has_children' ,
      'expanded' ,
      'depth' ,
      'customized' ,
      'p1' ,
      'p2' ,
      'p3' ,
      'p4' ,
      'p5' ,
      'p6' ,
      'p7' ,
      'p8' ,
      'p9' ,
      'updated' ,
    ));
  }

  function prepareRow($row) {
    // Convert the alias to the node path.
    $node_path = drupal_lookup_path('source', $row->link_path);
    if ($node_path == FALSE) {
      return FALSE;
    }

    $row->link_path = $node_path;
  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('mlid', 'mlid');
    $columns[1] = array('ref_parent', 'ref_parent');
    $columns[2] = array('link_path', 'link_path');
    $columns[3] = array('link_title', 'link_title');
    $columns[4] = array('weight', 'weight');
    return $columns;
  }

}
