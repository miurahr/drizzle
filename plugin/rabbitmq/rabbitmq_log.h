/* - mode: c; c-basic-offset: 2; indent-tabs-mode: nil; -*-
 *  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 *
 *  Copyright (C) 2010 Marcus Eriksson
 *
 *  Authors:
 *
 *  Marcus Eriksson <krummas@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#pragma once

#include <drizzled/replication_services.h>
#include <drizzled/plugin/transaction_applier.h>
#include <string>
#include "rabbitmq_handler.h"

namespace drizzle_plugin
{

/**
 * @brief
 *   A TransactionApplier that sends the transactions to rabbitmq
 *   (or any AMQP 0-8 compliant message queue)
 *
 * @details
 *   Connects to rabbitmq server in constructor, publishes messages
 *   in apply(...). If error occurs, the plugin disables itself.
 */
class RabbitMQLog :
  public drizzled::plugin::TransactionApplier 
{
private:
  RabbitMQHandler* _rabbitMQHandler;
  const std::string _exchange;
  const std::string _routingkey;
public:

  /**
   * @brief
   *   Constructs a new RabbitMQLog.
   *
   * @details
   *  Takes an instance of RabbitMHandler and uses that for rabbitmq communication
   *
   * @param[in] mqHandler name of the plugin, typically rabbitmq_log.
   */
  RabbitMQLog(const std::string &name,
              const std::string &exchange,
              const std::string &routingkey,
              RabbitMQHandler* mqHandler);
  ~RabbitMQLog();

  /**
   * @brief
   *   Serializes the transaction and uses a RabbiMQHandler to publish the message.
   *
   * @details
   *   Serializes the protobuf transaction and drops it on rabbitmq
   *
   * @param[in] to_apply the transaction to send
   */
  drizzled::plugin::ReplicationReturnCode
  apply(drizzled::Session &session, const drizzled::message::Transaction &to_apply);

};

} /* namespace drizzle_plugin */

