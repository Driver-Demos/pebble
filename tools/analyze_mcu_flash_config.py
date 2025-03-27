# Copyright 2024 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import binutils
import os.path
import sh


class Config(object):
    def abs_path(self, script_relative_path):
        return os.path.join(
            os.path.dirname(os.path.realpath(__file__)),
            script_relative_path)

    def default_elf_abs_path(self):
        return self.abs_path(self.rel_elf_path())

    def rel_elf_path(self):
        raise Exception("Implement me!")

    def lib_paths(self):
        return []

    def lib_symbols(self):
        # Array of tuples (use_fast, lib_path):
        lib_paths = self.lib_paths()

        def extract_symbols(object_path):
            nm = binutils.nm_generator(object_path)
            return set([s for _, _, s, _, _, _ in nm])

        return {path: extract_symbols(path)
                for path in lib_paths}

    def memory_region_to_analyze(self):
        raise Exception("Implement me!")

    def apply_tree_tweaks(self, tree):
        pass


class TintinElfConfig(Config):
    def rel_elf_path(self):
        return '../build/src/fw/tintin_fw.elf'

    def memory_region_to_analyze(self):
        FLASH_START = 0x8008000
        FLASH_END = FLASH_START + (512 * 1024)
        FLASH_REGION = (FLASH_START, FLASH_END)
        return FLASH_REGION

    def lib_paths(self):
        return []

    def apply_tree_tweaks(self, tree):
        # Manually add in the bootloader + gap:
        tree["Bootloader"] = 0x8000
        tree["Bootloader-FW-Gap"] = 0x8000


class DialogElfConfig(Config):
    def memory_region_to_analyze(self):
        # Just spelling out both regions here in case someone wants to tweak:
        sysram_start = 0x7FC0000
        sysram_end = sysram_start + (128 * 1024)
        cacheram_start = 0x7FE0000
        cacheram_end = cacheram_start + (16 * 1024)
        return (sysram_start, cacheram_end)


class DialogBootElfConfig(DialogElfConfig):
    def rel_elf_path(self):
        return '../build/src/bluetooth-fw/da1468x/controller/' \
               'boot/bt_da14681_boot.elf'


class DialogMainElfConfig(DialogElfConfig):
    def rel_elf_path(self):
        return '../build/src/bluetooth-fw/da1468x/controller/' \
               'main/bt_da14681_main.elf'

    def lib_paths(self):
        libble_stack_path = self.abs_path(
            '../src/bluetooth-fw/da1468x/vendor/bt-dialog-sdk/sdk/interfaces/'
            'ble_stack/DA14681-01-Debug/libble_stack_da14681_01.a')
        return [libble_stack_path]

CONFIG_CLASSES = {
    'tintin': TintinElfConfig,
    'dialog-boot': DialogBootElfConfig,
    'dialog-main': DialogMainElfConfig,
}
