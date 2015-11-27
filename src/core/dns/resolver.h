//: ----------------------------------------------------------------------------
//: Copyright (C) 2014 Verizon.  All Rights Reserved.
//: All Rights Reserved
//:
//: \file:    resolver.h
//: \details: TODO
//: \author:  Reed P. Morrison
//: \date:    02/07/2014
//:
//:   Licensed under the Apache License, Version 2.0 (the "License");
//:   you may not use this file except in compliance with the License.
//:   You may obtain a copy of the License at
//:
//:       http://www.apache.org/licenses/LICENSE-2.0
//:
//:   Unless required by applicable law or agreed to in writing, software
//:   distributed under the License is distributed on an "AS IS" BASIS,
//:   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//:   See the License for the specific language governing permissions and
//:   limitations under the License.
//:
//: ----------------------------------------------------------------------------
#ifndef _RESOLVER_H
#define _RESOLVER_H

//: ----------------------------------------------------------------------------
//: Includes
//: ----------------------------------------------------------------------------
#include "ndebug.h"
#include "hlx/hlx.h"

#include <pthread.h>

#include <string>
#include <map>

//: ----------------------------------------------------------------------------
//: Constants
//: ----------------------------------------------------------------------------
#define RESOLVER_DEFAULT_AI_CACHE_FILE "/tmp/addr_info_cache.json"

//: ----------------------------------------------------------------------------
//: Types
//: ----------------------------------------------------------------------------
namespace ns_hlx {

// TODO Create struct with TTL for storing ai cache
typedef std::map <std::string, std::string> ai_cache_map_t;

// Host info
typedef struct host_info_struct {
        struct sockaddr_in m_sa;
        int m_sa_len;
        int m_sock_family;
        int m_sock_type;
        int m_sock_protocol;

        host_info_struct():
                m_sa(),
                m_sa_len(16),
                m_sock_family(AF_INET),
                m_sock_type(SOCK_STREAM),
                m_sock_protocol(IPPROTO_TCP)
        {
                m_sa.sin_family = AF_INET;
        };

        void show(void)
        {
                printf("+-----------+\n");
                printf("| Host Info |\n");
                printf("+-----------+-------------------------\n");
                printf(": m_sock_family:   %d\n", m_sock_family);
                printf(": m_sock_type:     %d\n", m_sock_type);
                printf(": m_sock_protocol: %d\n", m_sock_protocol);
                printf(": m_sa_len:        %d\n", m_sa_len);
                printf("+-------------------------------------\n");
        };

} host_info_t;

//: ----------------------------------------------------------------------------
//: \details: TODO
//: ----------------------------------------------------------------------------
class resolver
{
public:
        // -------------------------------------------------
        // Public methods
        // -------------------------------------------------
        resolver();
        ~resolver();
        int32_t init(std::string addr_info_cache_file = "", bool a_use_cache = false);
        int32_t cached_resolve(const std::string &a_host,
                               uint16_t a_port,
                               host_info_t &a_host_info,
                               std::string &ao_error);
        int32_t sync_ai_cache(void);
        int32_t read_ai_cache(const std::string &a_ai_cache_file);

private:
        // -------------------------------------------------
        // Private methods
        // -------------------------------------------------
        DISALLOW_COPY_AND_ASSIGN(resolver)

        // -------------------------------------------------
        // Private members
        // -------------------------------------------------
        bool m_is_initd;
        uint32_t m_use_cache;
        pthread_mutex_t m_cache_mutex;
        ai_cache_map_t m_ai_cache_map;
        std::string m_ai_cache_file;
};

} //namespace ns_hlx {

#endif