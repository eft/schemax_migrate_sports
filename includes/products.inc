<?php

/*
 * @file
 * Migration for products
 */

class SchemaxMigrationSportsProducts extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/products.csv';

    $this->description = t('Import products into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'sku' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
        'description' => 'Product SKU',
      ),
        ), MigrateDestinationEntityAPI::getKeySchema('commerce_product', 'schemax_product_type')
    );

    $this->destination = new MigrateDestinationEntityAPI('commerce_product', 'schemax_product_type');

    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('commerce_price', 'price');

    // Add mapping for images linked to the node
    //
    // Define where the incoming images are stored
    $source_images_path = drupal_get_path('module', 'schemax_migrate_sports') . '/images';

    // Map the name of the incoming file destination field
    $this->addFieldMapping('field_image', 'imagename');
    // Make sure the source location is also mapped
    $this->addFieldMapping('field_image:source_dir')
        ->defaultValue($source_images_path);

    // Hard code uid to registrar user
    $this->addFieldMapping('uid')
           ->defaultValue(5)
           ->sourceMigration('Users');

    $this->addUnmigratedDestinations(array(
      'created',
      'changed',
      'status',
      'language',
      'revision_id',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('sku', 'sku');
    $columns[1] = array('title', 'title');
    $columns[2] = array('price', 'price');
    $columns[3] = array('imagename', 'imagename');
    return $columns;
  }

}
