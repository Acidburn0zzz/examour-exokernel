/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** ExAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** ExAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include    <stdbool.h>
#include    <stdlib.h>

#include    <CuTest.h>

#include    "../include/gdt.h"

void    Testgdt_create_with_null_pointer(CuTest *tc)
{
  bool  ret;

  ret = gdt_create(NULL);
  CuAssertTrue(tc, !ret);
}

void    Testgdt_create(CuTest *tc)
{
  gdt_t *context;
  bool  ret;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  free(context);
}

void    Testgdt_destroy_with_null_pointer(CuTest *tc)
{
  bool  ret;

  ret = gdt_destroy(NULL);
  CuAssertTrue(tc, !ret);
}

void    Testgdt_destroy(CuTest *tc)
{
  gdt_t *context;
  bool  ret;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_destroy(context);
  CuAssertTrue(tc, ret);
  free(context);
}

void    Testgdt_add_entry_with_null_context(CuTest *tc)
{
  bool  ret;
  uint16_t  index;

  ret = gdt_add_entry(NULL, 0, 42, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB, &index);
  CuAssertTrue(tc, !ret);
}

void    Testgdt_add_entry_with_null_index(CuTest *tc)
{
  bool  ret;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry(context, 0, 42, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB, NULL);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testgdt_add_entry_with_null_invalid_size(CuTest *tc)
{
  bool  ret;
  uint16_t  index;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry(context, 0, 0, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB, &index);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testgdt_add_entry(CuTest *tc)
{
  bool  ret;
  gdt_t *context;
  uint16_t  index;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry(context, 0, 42, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB, &index);
  CuAssertTrue(tc, ret);
  free(context);
}

void    Testgdt_add_entry_at_with_null_context(CuTest *tc)
{
  bool  ret;

  ret = gdt_add_entry_at(NULL, 1, 0, 42, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB);
  CuAssertTrue(tc, !ret);
}

void    Testgdt_add_entry_at_with_invalid_size(CuTest *tc)
{
  bool  ret;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry_at(context, 1, 0, 0, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testgdt_add_entry_at_invalid_index(CuTest *tc)
{
  bool  ret;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry_at(context, 0, 0, 42, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB);
  CuAssertTrue(tc, !ret);
  free(context);
}


void    Testgdt_add_entry_at(CuTest *tc)
{
  bool  ret;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry_at(context, 1, 0, 42, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB);
  CuAssertTrue(tc, ret);
  free(context);
}

void    Testgdt_add_entry_at_with_already_used_entry(CuTest *tc)
{
  bool  ret;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry_at(context, 1, 0, 42, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry_at(context, 1, 0, 42, SEGMENT_TYPE_DATA_RW | SEGMENT_16BITS | SEGMENT_GRANULARITY_4KB);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testgdt_remove_entry_with_null_context(CuTest *tc)
{
  bool  ret;

  ret = gdt_remove_entry(NULL, 0);
  CuAssertTrue(tc, !ret);
}

void    Testgdt_remove_entry_forbiden(CuTest *tc)
{
  bool  ret;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_remove_entry(context, 0);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testgdt_remove_entry_already_free(CuTest *tc)
{
  bool  ret;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_remove_entry(context, 1);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testgdt_remove_entry(CuTest *tc)
{
  bool  ret;
  gdt_t *context;

  context = malloc(sizeof(*context) * GDT_TABLE_SIZE);
  ret = gdt_create(context);
  CuAssertTrue(tc, ret);
  ret = gdt_add_entry_at(context, 1, 0, 42, SEGMENT_TYPE_DATA_RD | SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB);
  CuAssertTrue(tc, ret);
  ret = gdt_remove_entry(context, 1);
  CuAssertTrue(tc, ret);
  free(context);
}
