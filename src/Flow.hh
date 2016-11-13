/*
 * Copyright 2015 Applied Research Center for Computer Networks
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "FlowFwd.hh"

#include <cstdint>
#include <utility> // pair
#include <unordered_set>

#include "types/exception.hh"

// TODO: fully rewritten; note that 0.5 version contains a lot of comments

namespace runos {

class Flow {
public:
    enum class State {
        Egg,
        Active,
        Evicted,
        Idle,
        Expired,
    };

    Flow() noexcept;

    virtual State state() const
    { return m_state; }

    virtual uint64_t cookie() const
    { return m_cookie; }

    virtual void cookie(uint64_t cookie)
    { m_cookie = cookie; }

    // Returns (cookie_base, cookie_mask)
    static std::pair<uint64_t, uint64_t> cookie_space();

    virtual void evict() { } // = 0; //TODO
    virtual void kill() { } // = 0; //TODO

protected:
    State m_state {State::Egg};
    uint64_t m_cookie;
};

} // namespace runos
