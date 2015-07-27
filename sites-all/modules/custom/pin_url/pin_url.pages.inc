<?php

/**
 * @file pin_url.pages.inc
 */

/**
 * Form to create a Pin from a URL.
 */
function pin_url_create_form($form, &$form_state) {
  global $user;

  $step = isset($form_state['storage']['step']) ? $form_state['storage']['step'] : 1;

  $form['step-1'] = array(
    '#type' => 'submit',
    '#value' => '1. Website',
    '#attributes' => array('class' => array('form-progress-step')),
    '#weight' => -99,
  );
  $form['step-2'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => array('form-progress-step')),
    '#value' => '2. Image',
    '#weight' => -98,
  );
  $form['step-3'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => array('form-progress-step')),
    '#value' => '3. Pin',
    '#weight' => -97,
  );

  // Set the CSS class for the current step.
  $form['step-' . $step]['#attributes']['class'][] = 'active';

  // Keep track of the types of submit buttons to show.
  $next_submit = FALSE;
  $previous_submit = FALSE;
  $save_submit = FALSE;

  switch($step) {
    case 1:
      $next_submit = TRUE;

      $website = !empty($form_state['storage']['values'][1]['website']) ? $form_state['storage']['values'][1]['website'] : '';
      $form['website'] = array(
        '#type' => 'textfield',
        '#title' => 'Website',
        '#description' => t('Where do you want to Pin from?'),
        '#required' => TRUE,
        '#default_value' => $website,
        '#weight' => 1,
      );
      break;

    case 2:
      $next_submit = TRUE;
      $previous_submit = TRUE;

      $images = $form_state['storage']['website_images'];
      if (!empty($images)) {
        $themed_images = array('_none' => t('No Image'));
        foreach($images as $idx => $image_src) {
          $themed_images[$image_src] = pin_url_style_image($image_src);
        }

        $form['image'] = array(
          '#type' => 'radios',
          '#title' => t('Image for the Pin'),
          '#options' => $themed_images,
          '#description' => t('Select an image to represent this pin'),
          '#required' => TRUE,
          '#default_value' => '_none',
        );
      }
      break;

    case 3:
      $previous_submit = TRUE;
      $save_submit = TRUE;

      $pin_form = _pin_url_get_pin_form();
      dpm($pin_form, 'pin form');

      $form['title'] = $pin_form['title'];
      $form['notes'] = $pin_form['field_description'];
      $form['private'] = $pin_form['field_private'];
      $form['board'] = $pin_form['field_board'];

      $image_src = $form_state['storage']['values'][2]['image'];
      $form['image_to_pin'] = array(
        '#markup' => pin_url_style_image($image_src),
        '#weight' => 50,
      );

      break;

  }

  $form['buttons'] = array(
    '#type' => 'container',
  );
  if ($previous_submit) {
    $form['buttons']['previous'] = array(
      '#type' => 'submit',
      '#value' => 'Previous',
      '#weight' => 99,
      '#attributes' => array('style' => 'float: left'),
    );
  }
  if ($next_submit) {
    $form['buttons']['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#weight' => 100,
      '#attributes' => array('style' => 'float: right'),
    );
  }
  elseif ($save_submit) {
    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create'),
      '#weight' => 100,
      '#attributes' => array('style' => 'float: right'),
    );
  }

  dpm($form, 'form');
  dpm($form_state, 'form_state');

  return $form;
}

/**
 * Validation handler for creating a Pin from a URL.
 */
function pin_url_create_form_validate($form, &$form_state) {

  // Figure out what step we are on.
  $step = isset($form_state['storage']['step']) ? $form_state['storage']['step'] : 1;
  switch($step){
    case 1:
      $website = $form_state['values']['website'];
      if (!valid_url($website, TRUE)) {
        form_set_error('website', 'Please specify a valid URL.');
        // Do not continue on because the URL isn't valid.
        return;
      }

      // Get the images from the website, if any.
      // Do this now, because you ONLY want to perform this task
      // after submitting step #1, anfd not on refreshes of 'Previous' clicks.
      $form_state['storage']['website_images'] = pin_url_parse($website);
      break;

    case 2:

      break;

    case 3:

      break;
  }
}

/**
 * Submit handler for creating a Pin from a URL.
 */
function pin_url_create_form_submit($form, &$form_state) {

  if (!isset($form_state['storage']['step'])) {
    $form_state['storage']['step'] = 1;
  }

  // The current step.
  $step = $form_state['storage']['step'];
  $form_state['storage']['values'][$step] = $form_state['values'];

  // Move on to the next step.
  if ($form_state['clicked_button']['#id'] == 'edit-next') {
    $form_state['storage']['step'] = $step + 1;
  }
  // Go back to the previous step.
  else if ($form_state['clicked_button']['#id'] == 'edit-previous') {
    $form_state['storage']['step'] = $step - 1;
  }
  else if ($form_state['clicked_button']['#id'] == 'edit-submit') {
    // Save the data.
    $website = $form_state['values']['website'];
  }
  else {
    // Go to a step.
    switch($form_state['clicked_button']['#id']){
      case 'edit-step-1':
        $form_state['storage']['step'] = 1;
        break;

      case 'edit-step-2':
        $form_state['storage']['step'] = 2;
        break;

      case 'edit-step-3':
        $form_state['storage']['step'] = 3;
        break;
    }
  }

  // In some instances where there are more than 2 steps,
  // the 'form_build_id' gets lost???
  if (isset($form_state['storage']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['storage']['form_build_id'];
  }
  $form_state['storage']['form_build_id'] = $form_state['values']['form_build_id'];

  // We didn't save a new Pin, so rebuild the form.
  $form_state['rebuild'] = TRUE;
}

/**
 * Get a Pin node form.
 */
function _pin_url_get_pin_form() {
  global $user;

  // Prepare an empty node.
  $blank_pin = array(
    'type' => 'pin',
    'uid' => $user->uid,
    'name' => $user->name,
  );
  $pin = (object)$blank_pin;
  node_object_prepare( $pin );

  // Load the required include file.
  module_load_include('inc', 'node', 'node.pages');

  return drupal_get_form('pin_node_form', $pin);
}

/**
 * Parse a URL for images.
 *
 * @param string $html_url
 *   The URL to parse
 *
 * @return array
 *   Array of images found in the URL's HTML
 */
function pin_url_parse($html_url) {

  $html = file_get_contents($html_url);

  $doc = new DOMDocument();
  @$doc->loadHTML($html);

  $tags = $doc->getElementsByTagName('img');

  $image_urls = array();

  foreach ($tags as $tag) {
    $image = $tag->getAttribute('src');
    $check = parse_url($image);
    if (empty($check['host']) && empty($check['scheme'])) {
      $image = $html_url . $image;
    }

    // Check if it's an image.
    $valid = FALSE;
    $url_headers = get_headers($image, 1);
    if (!empty($url_headers['Content-Type'])) {
      $type = strtolower($url_headers['Content-Type']);
      // Does the media type start with 'image/'.
      $valid = !empty($type) || strrpos($type, 'image/', -strlen($type)) !== FALSE;
    }

    // Keep it, if valid.
    if ($valid) {
      $image_urls[] = $image;
    }
  }
  return $image_urls;
}

/**
 * Generate HTML for an image.
 *
 * @param array $image_src
 *   Absolute image URL
 *
 * @return array
 *   Themed image HTML
 */
function pin_url_style_image($image_src) {

  $attrs = array('class' => 'some-img');
  return theme_image(array('path' => $image_src, 'attributes' => $attrs));
}
