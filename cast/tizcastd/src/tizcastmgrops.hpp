/**
 * Copyright (C) 2011-2017 Aratelia Limited - Juan A. Rubio
 *
 * This file is part of Tizonia
 *
 * Tizonia is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Tizonia is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Tizonia.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file   tizcastmgrops.hpp
 * @author Juan A. Rubio <juan.rubio@aratelia.com>
 *
 * @brief  Cast manager operations
 *
 *
 */

#ifndef TIZCASTMGROPS_HPP
#define TIZCASTMGROPS_HPP

#include <boost/function.hpp>
#include <string>

#include <OMX_Core.h>

#include <tizchromecast_c.h>
#include <tizchromecasttypes.h>

#include "tizcastmgrtypes.hpp"

namespace tiz
{
  namespace castmgr
  {
    // Forward declarations
    class mgr;
    void cc_cast_status_cback (void *ap_user_data,
                               tiz_chromecast_cast_status_t a_status);

    void cc_media_status_cback (void *ap_user_data,
                                tiz_chromecast_media_status_t a_status);

    /**
     *  @class ops
     *  @brief The cast manager operations class.
     *
     */
    class ops
    {
      friend void cc_cast_status_cback (void *, tiz_chromecast_cast_status_t);

      friend void cc_media_status_cback (void *, tiz_chromecast_media_status_t);

    public:
      typedef boost::function< void(OMX_ERRORTYPE, std::string) >
          termination_callback_t;

    public:
      ops (mgr *p_mgr, cast_status_cback_t cast_cb,
           media_status_cback_t media_cb);
      virtual ~ops ();

      void deinit ();

    public:
      void do_connect (const std::string &name_or_ip);
      void do_disconnect ();
      void do_poll (int poll_time_ms);
      void do_load_url (const std::string &url, const std::string &mime_type,
                        const std::string &title);
      void do_play ();
      void do_stop ();
      void do_pause ();
      void do_volume_up ();
      void do_volume_down ();
      void do_mute ();
      void do_unmute ();
      void do_report_fatal_error (const int error, const std::string &msg);
      bool is_fatal_error (const int error, const std::string &msg);

      int internal_error () const;
      std::string internal_error_msg () const;

    private:
      mgr *p_mgr_;  // Not owned
      cast_status_cback_t cast_cb_;
      media_status_cback_t media_cb_;
      // termination_callback_t termination_cback_;
      int error_code_;
      std::string error_msg_;
      tiz_chromecast_t *p_cc_;
    };
  }  // namespace castmgr
}  // namespace tiz

#endif  // TIZCASTMGROPS_HPP