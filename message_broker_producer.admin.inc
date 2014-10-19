<?php

/**
 * @file
 * Content administration and module settings UI.
 */

/**
 * Configuration form
 */
function message_broker_producer_config_form($form, &$form_state) {

  $form['authentication'] = array(
    '#type' => 'fieldset',
    '#title' => t('RabbitMQ Authentication')
  );
  $form['authentication']['message_broker_producer_rabbitmq_host'] = array(
    '#type' => 'textfield',
    '#title' => t('host'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_rabbitmq_host', 'localhost'),
  );
  $form['authentication']['message_broker_producer_rabbitmq_port'] = array(
    '#type' => 'textfield',
    '#title' => t('port'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_rabbitmq_port', '5672'),
  );
  $form['authentication']['message_broker_producer_rabbitmq_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_rabbitmq_username', 'guest'),
  );
  $form['authentication']['message_broker_producer_rabbitmq_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_rabbitmq_password', 'guest'),
  );
  $form['authentication']['message_broker_producer_rabbitmq_vhost'] = array(
    '#type' => 'textfield',
    '#title' => t('vhost'),
    '#required' => FALSE,
    '#default_value' => variable_get('message_broker_producer_rabbitmq_vhost', ''),
  );

  $form['configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Producer Configuration')
  );
  $form['configuration']['message_broker_producer_application_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Application ID'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_application_id', '-1'),
  );

  return system_settings_form($form);
}

/**
 * List RabbitMQ status
 */
function message_broker_producer_status() {

  // RabbitMQ Managment API
  // http://hg.rabbitmq.com/rabbitmq-management/raw-file/rabbitmq_v3_3_5/priv/www/api/index.html

  // Control returned results
  // curl -i -u guest:guest 'http://localhost:15672/api/channels?sort=message_stats.publish_details.rate&sort_reverse=true&columns=name,message_stats.publish_details.rate,message_stats.deliver_get_details.rate'

  $rabbit_username = variable_get('message_broker_producer_rabbitmq_username', 'guest');
  $rabbit_password = variable_get('message_broker_producer_rabbitmq_password', 'guest');

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    'Content-type: application/json',
    'Accept: application/json'
  ));
  curl_setopt($ch, CURLOPT_USERPWD, "$rabbit_username:$rabbit_password");
  curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);

  $rabbit_management_api_urls = array(
    'api-aliveness-test' => variable_get('message_broker_producer_rabbitmq_host', 'localhost') .':15672/api/aliveness-test/' . variable_get('message_broker_producer_rabbitmq_vhost', '%2F'),
    'api-vhosts' => variable_get('message_broker_producer_rabbitmq_host', 'localhost') .':15672/api/vhosts',
    'api-overview' => variable_get('message_broker_producer_rabbitmq_host', 'localhost') .':15672/api/overview',
  );

  foreach ($rabbit_management_api_urls as $call => $rabbit_management_api_url) {
    curl_setopt($ch, CURLOPT_URL, $rabbit_management_api_url);
    $jsonResult = curl_exec($ch);
    $results = json_decode($jsonResult);

    switch ($call) {
      case 'api-aliveness-test':
        $status = array();
        if ($results) {
          $status[$call] = $results->status;
        }
        break;

      case 'api-vhosts':
        $vhosts = array();
        if ($results) {
          foreach ($results as $idx => $entry) {
            if (!isset($entry->send_oct)) {
              continue;
            }

            $name = $entry->name;
            $send_oct = $entry->send_oct;
            $vhosts[$name] = $send_oct;

          }
        }
        break;

      case 'api-overview':
        $overview = array();

        $overview['version'] = $results->rabbitmq_version;

        // Extract results for Servers/Listeners.
        $overview['nodes'] = array();
        if ($results) {
          foreach ($results->listeners as $idx => $listener) {
            $overview['nodes'][$listener->node]  = array(
              'protocol' => $listener->protocol,
              'port' => $listener->port,
              'ip_address' => $listener->ip_address,
            );
          }
        }

        // Extract results for various Counts.
        $overview['object_totals'] = array();
        if ($results) {
          foreach ($results->object_totals as $name => $count) {
            $overview['object_totals'][$name] = $count;
          }
        }

        // Extract results for Contexts.
        $overview['contexts'] = array();
        if ($results) {
          foreach ($results->contexts as $idx => $context) {
            $overview['contexts'][$idx] = array(
              'node' => $context->node,
              'description' => $context->description,
              'port' => $context->port,
            );
          }
        }

        // echo( $call . ': <pre>');
        // print_r($results);
        // echo('</pre>');
        break;
    }

    if (!$results) {
      drupal_set_message("No results for call to API '$call', " .
                          'check the connection to the Message Broker server.',
                          'error');
    }
  }

  // Test link to produce transactionals queue entry
  $test_links['all'] = 'Generate ' . l('test producer entry', 'admin/config/services/message-broker-producer/test') . '.';

  $test_links['campaign-signup'] = 'Generate ' . l('test campaign_signup producer entry', 'admin/config/services/message-broker-producer/test/campaign_signup') . '.';
  $test_links['campaign-reportback'] = 'Generate ' . l('test campaign_reportback producer entry', 'admin/config/services/message-broker-producer/test/campaign_reportback') . '.';
  $test_links['user-password'] = 'Generate ' . l('test user_password producer entry', 'admin/config/services/message-broker-producer/test/user_password') . '.';
  $test_links['user-register'] = 'Generate ' . l('test user_register producer entry', 'admin/config/services/message-broker-producer/test/user_register') . '.';
  $test_links['user-register-under'] = 'Generate ' . l('test user_register_under producer entry', 'admin/config/services/message-broker-producer/test/user_register_under') . '.';
  $test_links['campaign-signup-noname'] = 'Generate ' . l('test campaign_signup_noname producer entry', 'admin/config/services/message-broker-producer/test/campaign_signup_noname') . '.';
  $test_links['campaign-reportback-noname'] = 'Generate ' . l('test campaign_reportback_noname producer entry', 'admin/config/services/message-broker-producer/test/campaign_reportback_noname') . '.';

  return theme('message_broker_producer_status',
                array(
                  'status' => $status,
                  'vhosts' => $vhosts,
                  'overview' => $overview,
                  'test_links' => $test_links,
                ));
}

/*
 * Pass through function to allow parameters to a form via a hook_menu call to
 * message_broker_producer_production_options_form()
 *
 * @return
 *   Call to drupal_get_form for the message_broker_producer_production_options_form
 *   form that includes the additional parameter $target_production
 */
function message_broker_producer_production_options_update($target_production) {
  return drupal_get_form('message_broker_producer_production_options_form', $target_production);
}

/**
 * Manage production type options - create, update and delete.
 *
 * If there are only three arguments in the path it builds the add form and
 * adds a record. Otherwise it builds the update form where the fourth
 * argument is the machine_name of the production entry in the
 * message_broker_producer table.
 *
 * @parm
 *   $form: Array of form elements
 * @parm
 *   &$form_submit: Array of the stae of the form elements
 * @parm
 *   $target_production: Update/delete of a production record, $target_production will have a value
 *
 * @return
 *   $form: An array of the form elements
 */
function message_broker_producer_production_options_form($form, &$form_submit, $target_production = NULL) {

  $mb_config_settings = message_broker_producer_load_config_options();
  $exchanges[0] = '-- Select exchange --';
  foreach($mb_config_settings->rabbit->exchanges as $exchange) {
    $exchanges[$exchange->name] = $exchange->name;
  }

  if ($target_production == NULL) {
    $form_action = 'Add';
    $selected_exchange = '';
  }
  else {
    $form_action = 'Update';
  }

  // List Queues
  // /api/queues/vhost
  // A list of all queues in a given virtual host.

  // List exchanges
  // /api/exchanges/vhost
  // A list of all exchanges in a given virtual host.

  // List bindings
  // /api/bindings/vhost/e/exchange/q/queue
  // A list of all bindings between an exchange and a queue. Remember, an exchange and a queue can be bound together many times!

  // Produce listing of all "production" entries
  /*
  '#options' => array(
    0 => t('No'),
    1 => t('Yes'),
  ),
  */
  // Allow selection of the same exchange in multipul production entries.

  // Pull out exchanges for listing in multiselect
  $form['message_broker_producer_production_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Production Name'),
    '#description' => t('A unique machine friendly production name to be referenced to access specific production entries.'),
    '#required' => FALSE,
    '#default_value' => '',
  );
  $form['message_broker_producer_exchanges'] = array(
    '#type' => 'select',
    '#title' => t('Select Exchange(s)'),
    '#options' => $exchanges,
    '#default_value' => $selected_exchange,
    '#description' => t('Select an exchange to send production requeusts to.'),
  );
  $form['message_broker_producer_enabled'] = array(
    '#type' => 'radios',
    '#title' => t('Enable/Disable Production'),
    '#default_value' => $target_production ? $record->enabled : 0,
    '#options' => array(
      1 => 'Enable production',
      0 => 'Disable production',
    ),
    '#weight' => 90,
    '#attributes' => $enabled ? array('class' => array('enabled')) : array('class' => array('disabled')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Add Production Type',
    '#weight' => 100,
  );
  $form['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/config/services/message-broker-producer'),
    '#weight' => 101,
  );

  // Validate and submit functions

  return $form;
}

/**
 * Validate form submissions from message_broker_producer_production_options_form().
 *
 * Check to make sute the production name is unique.
 */
function message_broker_producer_production_options_form_validate($form, &$form_state) {

  if ($production_name_exists) {
    form_set_error('message_broker_producer_production_name', t('The production name (!production_name) already exists. Use a unique name or delete the existing entry first.', array('!production_name' => $form_state['values']['message_broker_producer_production_name'])));
  }

}

/**
 * Process data submitted from message_broker_producer_production_options_form().
 */
function message_broker_producer_production_options_form_submit() {

  // INSERT

}

/**
 * Load mb_config.json from library and format as PHP object.
 */
function message_broker_producer_load_config_options() {

  $mb_config_library = libraries_load('messagebroker-config');

  if ($mb_config_library['loaded']) {
    // $mb_config_path = $GLOBALS['base_url'] . '/' . $mb_config_library['library path'] . '/mb_config.json';
    $mb_config_path = $mb_config_library['library path'] . '/mb_config.json';
    // $mb_config_json = file_get_contents($mb_config_path);
    $mb_config_json = implode(file($mb_config_path));
    $mb_config_settings = json_decode($mb_config_json);
    return $mb_config_settings;
  }
  else {
    drupal_set_error('Message Broker Configuration library failed to load.', 'error');
  }

}
