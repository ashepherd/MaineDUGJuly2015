<?php
/**
 * @file
 * homepins.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function homepins_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_categories:categories
  $menu_links['main-menu_categories:categories'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'categories',
    'router_path' => 'categories',
    'link_title' => 'Categories',
    'options' => array(
      'identifier' => 'main-menu_categories:categories',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: main-menu_home:<front>
  $menu_links['main-menu_home:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'identifier' => 'main-menu_home:<front>',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_pinners:pinners
  $menu_links['main-menu_pinners:pinners'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'pinners',
    'router_path' => 'pinners',
    'link_title' => 'Pinners',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_pinners:pinners',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: user-menu_board:node/add/board
  $menu_links['user-menu_board:node/add/board'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/board',
    'router_path' => 'node/add/board',
    'link_title' => 'Board',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_board:node/add/board',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'user-menu_create:node/add/pin',
  );
  // Exported menu link: user-menu_create:node/add/pin
  $menu_links['user-menu_create:node/add/pin'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/pin',
    'router_path' => 'node/add/pin',
    'link_title' => 'Create',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_create:node/add/pin',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: user-menu_current-username:menutoken/55b4f40b903c8
  $menu_links['user-menu_current-username:menutoken/55b4f40b903c8'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'menutoken/55b4f40b903c8',
    'router_path' => 'menutoken/%',
    'link_title' => '[current-user:name]',
    'options' => array(
      'menu_token_link_path' => 'pinner/[current-user:name]',
      'menu_token_data' => array(
        'user' => array(
          'type' => 'user',
          'plugin' => 'user_context',
          'options' => array(),
        ),
      ),
      'menu_token_options' => array(
        'clear' => 0,
      ),
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'user-menu_current-username:menutoken/55b4f40b903c8',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: user-menu_log-out:user/logout
  $menu_links['user-menu_log-out:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'identifier' => 'user-menu_log-out:user/logout',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: user-menu_my-account:user
  $menu_links['user-menu_my-account:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My account',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-account:user',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: user-menu_pin:node/add/pin
  $menu_links['user-menu_pin:node/add/pin'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/pin',
    'router_path' => 'node/add/pin',
    'link_title' => 'Pin',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_pin:node/add/pin',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'user-menu_create:node/add/pin',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Board');
  t('Categories');
  t('Create');
  t('Home');
  t('Log out');
  t('My account');
  t('Pin');
  t('Pinners');
  t('[current-user:name]');

  return $menu_links;
}
