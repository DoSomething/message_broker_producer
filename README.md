##Message Broker Producer

This Drupal 7 module provides producer access to the Message Broker / Quicksilver system.
* Wrapper function for Object Library calls
* Administration pages:
  * RabbitMQ authentication configuration
  * Add/Edit/Delete Productions
    * Productions are a collection of settings for connecting to a RabbitMQ server that define exchange and related
    queue settings.
  * Queue status

### Requirements:
- Drupal 7
- Message Broker PHP Library - https://github.com/DoSomething/messagebroker-phplib

### Administration Access:
- Once the module is enable goto: `/admin/config/services/message-broker-producer`

-----
Sponsored by DoSomething.org
