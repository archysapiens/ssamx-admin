<?php
 
/**
 * ac_cred.inc.php: Secret Connection Credentials for a database class
 * @package Oracle
 */
 
/**
 * DB user name
 */
define('SCHEMA', 'system');
 
/**
 * DB Password.
 *
 * Note: In practice keep database credentials out of directories
 * accessible to the web server.
 */
define('PASSWORD', 'oracle');
 
/**
 * DB connection identifier
 */
define('DATABASE', '192.168.1.65/orcl');
 
/**
 * DB character set for returned data
 */
define('CHARSET', 'UTF8');
 
/**
 * Client Information text for DB tracing
 */
define('CLIENT_INFO', 'AnyCo Corp.');
 
?>


ac_cred.inc.php