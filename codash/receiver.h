
/* Copyright (c) 2012, EFPL/Blue Brain Project
 *                     Daniel Nachbaur <daniel.nachbaur@epfl.ch>
 *
 * This file is part of CODASH <https://github.com/BlueBrain/codash>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef CODASH_RECEIVER_H
#define CODASH_RECEIVER_H

#include <dash/types.h>

#include <co/connectionDescription.h>
#include <co/objectVersion.h>


namespace codash
{
namespace detail { class Receiver; }

using lunchbox::uint128_t;

/**
 * The receiver side of the codash communicator pattern.
 *
 * This receiver can use an existing Collage localNode for communication or it
 * creates its own using the provided connection description.
 * This class is intended to receive dash nodes + changes on them from a
 * connected sender. This receiver maintains an own dash context used for
 * holding received nodes.
 */
class Receiver
{
public:
    /**
     * Construct a receiver with the given connection.
     *
     * The created localnode is maintained by the receiver. It will listen on
     * the given connection description for an incoming sender. Additionally,
     * the underlying Collage library will be initialized.
     *
     * @param argc the command line argument count.
     * @param argv the command line argument values.
     * @param conn the listening connection of this receiver.
     * @version 0.1
     */
    Receiver( int argc, char** argv, co::ConnectionDescriptionPtr conn );

    /** Construct a receiver with the given localNode. @version 0.1 */
    Receiver( co::LocalNodePtr localNode );

    /** Destruct this receiver. @version 0.1 */
    ~Receiver();

    /** Completes the connection to the sender. @version 0.1 */
    void waitConnected();

    /** @return the dash::Context of this receiver. @version 0.1 */
    dash::Context& getContext();

    /** @return the list of all received dash::Nodes. @version 0.1 */
    const dash::Nodes& getNodes() const;

    /**
     * Receive new changes from the connected sender.
     *
     * @param version the version to synchronize
     * @version 0.1
     */
    void sync( const uint128_t& version = co::VERSION_HEAD );

private:
    detail::Receiver* const impl_;
};

}

#endif