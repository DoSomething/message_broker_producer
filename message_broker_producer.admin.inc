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
  $form['configuration']['exchange'] = array(
    '#type' => 'fieldset',
    '#title' => t('Exchange')
  );
  $form['configuration']['exchange']['message_broker_producer_exchange_transactional_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_exchange_transactional_name', 'transactionalExchange'),
  );
  $form['configuration']['exchange']['message_broker_producer_exchange_transactional_type'] = array(
    '#type' => 'textfield',
    '#title' => t('type'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_exchange_transactional_type', 'topc'),
  );
  $form['configuration']['exchange']['message_broker_producer_exchange_transactional_passive'] = array(
    '#type' => 'textfield',
    '#title' => t('passive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_exchange_transactional_passive', '0'),
  );
  $form['configuration']['exchange']['message_broker_producer_exchange_transactional_durable'] = array(
    '#type' => 'textfield',
    '#title' => t('durable'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_exchange_transactional_durable', '1'),
  );
  $form['configuration']['exchange']['message_broker_producer_exchange_transactional_auto_delete'] = array(
    '#type' => 'textfield',
    '#title' => t('auto_delete'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_exchange_transactional_auto_delete', '0'),
  );

  $form['configuration']['queues'] = array(
    '#type' => 'fieldset',
    '#title' => t('Queues')
  );
  $form['configuration']['queues']['userRegistrationQueue'] = array(
    '#type' => 'fieldset',
    '#title' => t('userRegistrationQueue')
  );
  $form['configuration']['queues']['userRegistrationQueue']['message_broker_producer_queue_registrations_name'] = array(
    '#type' => 'textfield',
    '#title' => t('name'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_registrations_name', 'userRegistrationQueue'),
  );
  $form['configuration']['queues']['userRegistrationQueue']['message_broker_producer_queue_registrations_passive'] = array(
    '#type' => 'textfield',
    '#title' => t('passive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_registrations_passive', '0'),
  );
  $form['configuration']['queues']['userRegistrationQueue']['message_broker_producer_queue_registrations_durable'] = array(
    '#type' => 'textfield',
    '#title' => t('durable'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_registrations_durable', '1'),
  );
  $form['configuration']['queues']['userRegistrationQueue']['message_broker_producer_queue_registrations_exclusive'] = array(
    '#type' => 'textfield',
    '#title' => t('exclusive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_registrations_exclusive', '0'),
  );
  $form['configuration']['queues']['userRegistrationQueue']['message_broker_producer_queue_registrations_auto_delete'] = array(
    '#type' => 'textfield',
    '#title' => t('auto_delete'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_registrations_auto_delete', '0'),
  );
  $form['configuration']['queues']['userRegistrationQueue']['message_broker_producer_queue_registrations_bindingKey'] = array(
    '#type' => 'textfield',
    '#title' => t('bindingKey'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_registrations_bindingKey', 'user.registration.*'),
  );

  $form['configuration']['queues']['mailchimpCampaignSignupQueue'] = array(
    '#type' => 'fieldset',
    '#title' => t('mailchimpCampaignSignupQueue')
  );
  $form['configuration']['queues']['mailchimpCampaignSignupQueue']['message_broker_producer_queue_campaign_signups_name'] = array(
    '#type' => 'textfield',
    '#title' => t('name'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_campaign_signups_name', 'mailchimpCampaignSignupQueue'),
  );
  $form['configuration']['queues']['mailchimpCampaignSignupQueue']['message_broker_producer_queue_campaign_signups_passive'] = array(
    '#type' => 'textfield',
    '#title' => t('passive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_campaign_signups_passive', '0'),
  );
  $form['configuration']['queues']['mailchimpCampaignSignupQueue']['message_broker_producer_queue_campaign_signups_durable'] = array(
    '#type' => 'textfield',
    '#title' => t('durable'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_campaign_signups_durable', '1'),
  );
  $form['configuration']['queues']['mailchimpCampaignSignupQueue']['message_broker_producer_queue_campaign_signups_exclusive'] = array(
    '#type' => 'textfield',
    '#title' => t('exclusive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_campaign_signups_exclusive', '0'),
  );
  $form['configuration']['queues']['mailchimpCampaignSignupQueue']['message_broker_producer_queue_campaign_signups_auto_delete'] = array(
    '#type' => 'textfield',
    '#title' => t('auto_delete'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_campaign_signups_auto_delete', '0'),
  );
  $form['configuration']['queues']['mailchimpCampaignSignupQueue']['message_broker_producer_queue_campaign_signups_bindingKey'] = array(
    '#type' => 'textfield',
    '#title' => t('bindingKey'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_campaign_signups_bindingKey', 'campaign.signup.*'),
  );

  $form['configuration']['queues']['transactionalQueue'] = array(
    '#type' => 'fieldset',
    '#title' => t('transactionalQueue')
  );
  $form['configuration']['queues']['transactionalQueue']['message_broker_producer_queue_transactional_name'] = array(
    '#type' => 'textfield',
    '#title' => t('name'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_transactional_name', 'transactionalQueue'),
  );
  $form['configuration']['queues']['transactionalQueue']['message_broker_producer_queue_transactional_passive'] = array(
    '#type' => 'textfield',
    '#title' => t('passive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_transactional_passive', '0'),
  );
  $form['configuration']['queues']['transactionalQueue']['message_broker_producer_queue_transactional_durable'] = array(
    '#type' => 'textfield',
    '#title' => t('durable'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_transactional_durable', '1'),
  );
  $form['configuration']['queues']['transactionalQueue']['message_broker_producer_queue_transactional_exclusive'] = array(
    '#type' => 'textfield',
    '#title' => t('exclusive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_transactional_exclusive', '0'),
  );
  $form['configuration']['queues']['transactionalQueue']['message_broker_producer_queue_transactional_auto_delete'] = array(
    '#type' => 'textfield',
    '#title' => t('auto_delete'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_transactional_auto_delete', '0'),
  );
  $form['configuration']['queues']['transactionalQueue']['message_broker_producer_queue_transactional_bindingKey'] = array(
    '#type' => 'textfield',
    '#title' => t('bindingKey'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_transactional_bindingKey', '*.*.transactional'),
  );

  $form['configuration']['queues']['userAPIRegistrationQueue'] = array(
    '#type' => 'fieldset',
    '#title' => t('userAPIRegistrationQueue')
  );
  $form['configuration']['queues']['userAPIRegistrationQueue']['message_broker_producer_queue_userAPIRegistration_name'] = array(
    '#type' => 'textfield',
    '#title' => t('name'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPIRegistration_name', 'userAPIRegistrationQueue'),
  );
  $form['configuration']['queues']['userAPIRegistrationQueue']['message_broker_producer_queue_userAPIRegistration_passive'] = array(
    '#type' => 'textfield',
    '#title' => t('passive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPIRegistration_passive', '0'),
  );
  $form['configuration']['queues']['userAPIRegistrationQueue']['message_broker_producer_queue_userAPIRegistration_durable'] = array(
    '#type' => 'textfield',
    '#title' => t('durable'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPIRegistration_durable', '1'),
  );
  $form['configuration']['queues']['userAPIRegistrationQueue']['message_broker_producer_queue_userAPIRegistration_exclusive'] = array(
    '#type' => 'textfield',
    '#title' => t('exclusive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPIRegistration_exclusive', '0'),
  );
  $form['configuration']['queues']['userAPIRegistrationQueue']['message_broker_producer_queue_userAPIRegistration_auto_delete'] = array(
    '#type' => 'textfield',
    '#title' => t('auto_delete'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPIRegistration_auto_delete', '0'),
  );
  $form['configuration']['queues']['userAPIRegistrationQueue']['message_broker_producer_queue_userAPIRegistration_bindingKey'] = array(
    '#type' => 'textfield',
    '#title' => t('bindingKey'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPIRegistration_bindingKey', 'user.registration.*'),
  );

  $form['configuration']['queues']['userAPICampaignActivityQueue'] = array(
    '#type' => 'fieldset',
    '#title' => t('userAPIRegistrationQueue')
  );
  $form['configuration']['queues']['userAPICampaignActivityQueue']['message_broker_producer_queue_userAPIRegistration_userAPICampaignActivity_name'] = array(
    '#type' => 'textfield',
    '#title' => t('name'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPICampaignActivity_name', 'userAPIRegistrationQueue'),
  );
  $form['configuration']['queues']['userAPICampaignActivityQueue']['message_broker_producer_queue_userAPICampaignActivity_passive'] = array(
    '#type' => 'textfield',
    '#title' => t('passive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPICampaignActivity_passive', '0'),
  );
  $form['configuration']['queues']['userAPICampaignActivityQueue']['message_broker_producer_queue_userAPICampaignActivity_durable'] = array(
    '#type' => 'textfield',
    '#title' => t('durable'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPICampaignActivity_durable', '1'),
  );
  $form['configuration']['queues']['userAPICampaignActivityQueue']['message_broker_producer_queue_userAPICampaignActivity_exclusive'] = array(
    '#type' => 'textfield',
    '#title' => t('exclusive'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPICampaignActivity_exclusive', '0'),
  );
  $form['configuration']['queues']['userAPICampaignActivityQueue']['message_broker_producer_queue_userAPICampaignActivity_auto_delete'] = array(
    '#type' => 'textfield',
    '#title' => t('auto_delete'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPICampaignActivity_auto_delete', '0'),
  );
  $form['configuration']['queues']['userAPICampaignActivityQueue']['message_broker_producer_queue_userAPICampaignActivity_bindingKey'] = array(
    '#type' => 'textfield',
    '#title' => t('bindingKey'),
    '#required' => TRUE,
    '#default_value' => variable_get('message_broker_producer_queue_userAPICampaignActivity_bindingKey', 'campaign.*.*'),
  );

  return system_settings_form($form);
}

/**
 * List RabbitMQ status
 */
function message_broker_producer_status() {

  $status = '';

  // List queues
  /* @todo: permission access issues for www user
   *
   * http://unix.stackexchange.com/questions/15264/executing-a-shell-command-from-php-with-shell-exec
   * Added:
   * http    ALL=(username) /usr/local/sbin/rabbitmqctl
   * to /etc/sudoers
   *
   * Program Execution in PHP: exec, system, passthru, and shell_exec, oh my!
   * http://chipmunkninja.com/Program-Execution-in-PHP%3A-exec-m@
   *
   * works
   * $directoryListing = shell_exec('ls -la /usr/local/sbin');
   */
  $queues = shell_exec('/usr/local/sbin/rabbitmqctl list_queues');
  if ($queues == NULL) {
    $status['queues'] = 'Queue Listing - No RabbitMQ queues found, check that RabbitMQ is running.';
  }
  else {
    $status['queues'] = print_r($queues, TRUE);
  }

  // List exchanges
  $exchanges = shell_exec('/usr/local/sbin/rabbitmqctl list_exchanges');
  if ($exchanges == NULL) {
    $status['exchanges'] = 'Exchange Listing - No RabbitMQ exchanges found, check that RabbitMQ is running.';
  }

  // List bindings
  $bindings = shell_exec('rabbitmqctl list_exchanges');
  if ($bindings == NULL) {
    $status['bindings'] = 'Bindings Listing - No RabbitMQ bindings found, check that RabbitMQ is running.';
  }

  // Test link to produce tranactionals queue entry
  $test_links['all'] = 'Generate ' . l('test producer entry', 'admin/config/services/message-broker-producer/test') . '.';

  $test_links['campaign-signup'] = 'Generate ' . l('test campaign_signup producer entry', 'admin/config/services/message-broker-producer/test/campaign_signup') . '.';
  $test_links['campaign-reportback'] = 'Generate ' . l('test campaign_reportback producer entry', 'admin/config/services/message-broker-producer/test/campaign_reportback') . '.';
  $test_links['user-password'] = 'Generate ' . l('test user_password producer entry', 'admin/config/services/message-broker-producer/test/user_password') . '.';
  $test_links['user-register'] = 'Generate ' . l('test user_register producer entry', 'admin/config/services/message-broker-producer/test/user_register') . '.';
  $test_links['user-register-under'] = 'Generate ' . l('test user_register_under producer entry', 'admin/config/services/message-broker-producer/test/user_register_under') . '.';
  $test_links['campaign-signup-noname'] = 'Generate ' . l('test campaign_signup_noname producer entry', 'admin/config/services/message-broker-producer/test/campaign_signup_noname') . '.';
  $test_links['campaign-reportback-noname'] = 'Generate ' . l('test campaign_reportback_noname producer entry', 'admin/config/services/message-broker-producer/test/campaign_reportback_noname') . '.';
  
  return theme('message_broker_producer_status', array('status' => $status, 'test_links' => $test_links));
}
