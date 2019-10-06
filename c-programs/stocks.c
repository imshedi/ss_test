#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
        int32_t buy;
        int32_t sell;
} interval;

void stockbuysell(int32_t *price, int32_t n)
{
        int32_t i;
        int32_t count;
        interval sol[(n >> 1) + 1];

        /*! Prices must be given for at least two days */
        if (n == 1)
                return;

        for (i = 0, count = 0; i < n - 1; count++) {
                /*
                 * Find local minima.
                 * Note that the limit is (n-2) as we are comparing present
                 * element to the next element.
                 */
                while ((i < n - 1) && (price[i + 1] <= price[i]))
                        i++;

                /* If we reached the end, break as no further solution possible */
                if (i == n - 1)
                        break;

                /* Store the index of minima */
                sol[count].buy = i++;

                /*
                 * Find local maxima.
                 * Note that the limit is (n-1) as we are comparing to previous
                 * element.
                 */
                while ((i < n) && (price[i] >= price[i - 1]))
                        i++;

                /* Store the index of maxima */
                sol[count].sell = i - 1;
        }

        if (!count) {
                printf("There is no day when buying the stock will make profit\n");
                return;
        }

        for (i = 0; i < count; i++)
                printf("Buy on day: %d\t Sell on day: %d\n", sol[i].buy, sol[i].sell);
}

int32_t main(void)
{
        int32_t price[] = {100, 180, 260, 310, 40, 535, 695};

        stockbuysell(price, sizeof(price) / sizeof(price[0]));

        return EXIT_SUCCESS;
}
