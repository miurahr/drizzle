/* -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
 *  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 *
 *  Copyright (C) 2008 Sun Microsystems, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
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

#include <drizzled/select_result_interceptor.h>

namespace drizzled
{

class select_insert :public select_result_interceptor {
 public:
  TableList *table_list;
  Table *table;
  List<Item> *fields;
  uint64_t autoinc_value_of_last_inserted_row; // autogenerated or not
  CopyInfo info;
  bool insert_into_view;
  select_insert(TableList *table_list_par,
		Table *table_par, List<Item> *fields_par,
		List<Item> *update_fields, List<Item> *update_values,
		enum_duplicates duplic, bool ignore);
  ~select_insert();
  int prepare(List<Item> &list, Select_Lex_Unit *u);
  virtual int prepare2(void);
  bool send_data(List<Item> &items);
  virtual void store_values(List<Item> &values);
  virtual bool can_rollback_data() { return 0; }
  void send_error(drizzled::error_t errcode,const char *err);
  bool send_eof();
  void abort();
  /* not implemented: select_insert is never re-used in prepared statements */
  void cleanup();
};

} /* namespace drizzled */

