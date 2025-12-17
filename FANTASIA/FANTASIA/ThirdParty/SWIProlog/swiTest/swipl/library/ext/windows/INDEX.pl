/*  Creator: make/0

    Purpose: Provide index for autoload
*/

index((registry_get_key), 2, win_registry, registry).
index((registry_get_key), 3, win_registry, registry).
index((registry_set_key), 2, win_registry, registry).
index((registry_set_key), 3, win_registry, registry).
index((registry_delete_key), 1, win_registry, registry).
index((registry_lookup_key), 3, win_registry, registry).
index((win_flush_filetypes), 0, win_registry, registry).
index((shell_register_file_type), 4, win_registry, registry).
index((shell_register_file_type), 5, win_registry, registry).
index((shell_register_dde), 6, win_registry, registry).
index((shell_register_prolog), 1, win_registry, registry).
