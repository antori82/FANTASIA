/*  Creator: make/0

    Purpose: Provide index for autoload
*/

index((redis_server), 3, redis, redis).
index((redis_connect), 1, redis, redis).
index((redis_connect), 3, redis, redis).
index((redis_disconnect), 1, redis, redis).
index((redis_disconnect), 2, redis, redis).
index((redis), 1, redis, redis).
index((redis), 2, redis, redis).
index((redis), 3, redis, redis).
index((redis_get_list), 3, redis, redis).
index((redis_get_list), 4, redis, redis).
index((redis_set_list), 3, redis, redis).
index((redis_get_hash), 3, redis, redis).
index((redis_set_hash), 3, redis, redis).
index((redis_scan), 3, redis, redis).
index((redis_sscan), 4, redis, redis).
index((redis_hscan), 4, redis, redis).
index((redis_zscan), 4, redis, redis).
index((redis_subscribe), 4, redis, redis).
index((redis_subscribe), 2, redis, redis).
index((redis_unsubscribe), 2, redis, redis).
index((redis_current_subscription), 2, redis, redis).
index((redis_write), 2, redis, redis).
index((redis_read), 2, redis, redis).
index((redis_array_dict), 3, redis, redis).
index((redis_property), 2, redis, redis).
index((redis_current_command), 2, redis, redis).
index((redis_current_command), 3, redis, redis).
index((sentinel_slave), 4, redis, redis).
index((xstream_set), 3, redis_streams, redis_streams).
index((xadd), 4, redis_streams, redis_streams).
index((xlisten), 3, redis_streams, redis_streams).
index((xlisten_group), 5, redis_streams, redis_streams).
index((xconsumer_stop), 1, redis_streams, redis_streams).
