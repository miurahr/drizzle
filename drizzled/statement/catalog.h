/* - mode: c; c-basic-offset: 2; indent-tabs-mode: nil; -*-
 *  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 *
 *  Copyright (C) 2011 Brian Aker
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

#include <drizzled/statement.h>

namespace drizzled
{

namespace statement
{

class Catalog : public Statement
{
  identifier::Catalog _identifier;

public:
  Catalog(Session *in_session, drizzled::lex_string_t &arg);

  virtual bool authorized() const= 0;
  virtual bool perform() const= 0;

  bool execute();

  identifier::Catalog::const_reference identifier() const
  {
    return _identifier;
  }
};

} /* namespace statement */
} /* namespace drizzled */

#include <drizzled/statement/catalog/create.h>
#include <drizzled/statement/catalog/drop.h>

