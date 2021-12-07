/*!The Treasure Box Library
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Copyright (C) 2021-present, TBOOX Open Source Group.
 *
 * @author      sunzhenliang
 * @file        radix_sort.c
 * @ingroup     algorithm
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "radix_sort.h"
#include "../libc/libc.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */

static void print(int *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\t", a[i]);
    }
}

tb_void_t tb_radix_sort(tb_iterator_ref_t iterator, tb_size_t head, tb_size_t tail, tb_iterator_comp_t comp)
{
    // check
    tb_assert_and_check_return(iterator && (tb_iterator_mode(iterator) & TB_ITERATOR_MODE_FORWARD));
    tb_check_return(head != tail);

#define MAX 20
#define BASE 10
//#define SHOWPASS
    tb_size_t max = head;
    for (tb_size_t itor = tb_iterator_next(iterator, head); itor != tail; itor = tb_iterator_next(iterator, itor)) {
        if (tb_iterator_comp(iterator, tb_iterator_item(iterator, itor), tb_iterator_item(iterator, max)) > 0) {
            max = itor;
        }
    }

    tb_size_t       step = tb_iterator_step(iterator);
    tb_pointer_t temp[] = tb_malloc(step * tb_iterator_size(iterator));

    // void radixsort(int *a, int n) {
    int i, b[MAX], m = a[0], exp = 1;

    for (i = 1; i < n; i++) {
        if (a[i] > m) {
            m = a[i];
        }
    }

    while (m / exp > 0) {
        int bucket[BASE] = {0};

        for (i = 0; i < n; i++) {
            bucket[(a[i] / exp) % BASE]++;
        }

        for (i = 1; i < BASE; i++) {
            bucket[i] += bucket[i - 1];
        }

        for (i = n - 1; i >= 0; i--) {
            b[--bucket[(a[i] / exp) % BASE]] = a[i];
        }

        for (i = 0; i < n; i++) {
            a[i] = b[i];
        }

        exp *= BASE;
#ifdef SHOWPASS
        printf("\nPASS   : ");
        print(a, n);
#endif
    }
}

tb_void_t tb_radix_sort_all(tb_iterator_ref_t iterator, tb_iterator_comp_t comp)
{
    tb_radix_sort(iterator, tb_iterator_head(iterator), tb_iterator_tail(iterator), comp);
}

