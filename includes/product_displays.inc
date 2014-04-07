<?php

/*
 * @file
 * Migration for product displays
 */

class SchemaxMigrationSportsProductDisplays extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/product_displays.csv';

    $this->description = t('Import product displays into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'product_display_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Product Display ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNode('schemax_product_display');

    $this->addFieldMapping(NULL, 'product_display_id');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_schemax_product', 'sku');
    $this->addFieldMapping('field_schemax_catalog_category', 'category');
    $this->addFieldMapping('field_schemax_catalog_category:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_schemax_promotion', 'promotion');

    // Hard code uid to registrar user
    $this->addFieldMapping('uid')
        ->defaultValue(5)
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
    ));
  }

  // Convert text sku to integer value for product id
  public function prepareRow($row) {
      $product = commerce_product_load_by_sku($row->sku);
      $row->sku = $product->product_id;
  }

  // Define columns in source CSV file
  protected function csvcolumns() {
    $columns[0] = array('product_display_id', 'product_display_id');
    $columns[1] = array('title', 'title');
    $columns[2] = array('body', 'body');
    $columns[3] = array('sku', 'sku');
    $columns[4] = array('category', 'category');
    $columns[5] = array('promotion', 'promotion');
    return $columns;
  }

}
