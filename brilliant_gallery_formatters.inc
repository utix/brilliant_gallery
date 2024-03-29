<?php

/**
 * Implements hook_field_formatter_info().
 *
 */
function brilliant_gallery_field_formatter_info() {
  return array(
    'brilliant_gallery_render' => array(
      'label' => t('Brilliant Gallery: local path, BT Sync secret (default 33 bytes only), Picasa RSS link or Google+ album URL'),
      'field types' => array('text'),
    ),
    'brilliant_gallery_single' => array(
      'label' => t('A random image from Brilliant Gallery: local path, BT Sync secret (default 33 bytes only), Picasa RSS link or Google+ album URL'),
      'field types' => array('text'),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 *
 */
function brilliant_gallery_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  switch ($display['type']) {

    case 'brilliant_gallery_render':
      foreach ($items as $delta => $item) {
        //dpm($item);
        $pathurl = trim($item['value']);
        //$pathurl_btsync_check = brilliant_gallery_pathurl_btsync_check($pathurl);
        // If this is a BT Sync folder (secret), change $pathurl
        //if ($pathurl_btsync_check) $pathurl = $pathurl_btsync_check;
        //dpm('pathurl: '.$pathurl);
        if (function_exists('replace_brilliant_gallery_tags') AND $pathurl <> ''){
          $result = '';
          //$bgcode = '[bg|'.$pathurl.'|0|107|sort|100000|#ffffff]';
          $bgcode = '[bg|'.$pathurl.']';
          $gallery = replace_brilliant_gallery_tags($bgcode);
          //dpm(strip_tags($gallery));
          if (strip_tags($gallery) <> ''){ // Useful?
            $result .= $gallery; // <br clear=all><br clear=all>
          }
          $element[$delta] = array(
            '#markup' => $result,
          );
        }
      }
      break;

    case 'brilliant_gallery_single':
      foreach ($items as $delta => $item) {
        //dpm($item);
        $pathurl = trim($item['value']);
        //$pathurl_btsync_check = brilliant_gallery_pathurl_btsync_check($pathurl);
        // If this is a BT Sync folder (secret), change $pathurl
        //if ($pathurl_btsync_check) $pathurl = $pathurl_btsync_check;
        if (function_exists('replace_brilliant_gallery_tags') AND $pathurl <> ''){
          $result = '';
          // [bg|path/to/your/gallery/folder/without/wrapping/slashes |columncountoverride|widthoverride|sortorrandomoverride|maximumnumbertoshow|colouroverride|beginfromoverride|caption-yes-no-text]
          // maximumnumbertoshow = 1
          // random
          // columnoverride = 0 ... because it does not matter, we show just 1 image
          // widthoverride ... taken from settings
          $bgcode = '[bg|'.$pathurl.'|0|'.variable_get('brilliant_gallery_maximagewidth', 150).'|random|1]';
          $gallery = replace_brilliant_gallery_tags($bgcode);
          //dpm(strip_tags($gallery));
          if (strip_tags($gallery) <> ''){ // Useful?
            $result .= $gallery; // <br clear=all><br clear=all>
          }
          $element[$delta] = array(
            '#markup' => $result,
          );
        }
      }
      break;

  }

  //dpm($element);
  return $element;
}
