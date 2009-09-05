/*
    Copyright (c) 2007-2009 FastMQ Inc.

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_IO_OBJECT_HPP_INCLUDED__
#define __ZMQ_IO_OBJECT_HPP_INCLUDED__

#include <stddef.h>

#include "i_poller.hpp"
#include "i_poll_events.hpp"

namespace zmq
{

    //  Simple base class for objects that live in I/O threads.
    //  It makes communication with the poller object easier and
    //  makes defining unneeded event handlers unnecessary.

    class io_object_t : public i_poll_events
    {
    public:

        io_object_t (class io_thread_t *io_thread_ = NULL);
        ~io_object_t ();

    protected:

        //  Derived class can init/swap the underlying I/O thread.
        //  Caution: Remove all the file descriptors from the old I/O thread
        //  before swapping to the new one!
        void set_io_thread (class io_thread_t *io_thread_);

        //  Methods to access underlying poller object.
        handle_t add_fd (fd_t fd_);
        void rm_fd (handle_t handle_);
        void set_pollin (handle_t handle_);
        void reset_pollin (handle_t handle_);
        void set_pollout (handle_t handle_);
        void reset_pollout (handle_t handle_);
        void add_timer ();
        void cancel_timer ();

        //  i_poll_events interface implementation.
        void in_event ();
        void out_event ();
        void timer_event ();

    private:

        struct i_poller *poller;

        io_object_t (const io_object_t&);
        void operator = (const io_object_t&);
    };

}

#endif