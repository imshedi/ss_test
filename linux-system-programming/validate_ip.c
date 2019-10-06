#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE(arr) ((int32_t)(sizeof(arr) / sizeof(arr[0])))

int32_t main(void)
{
        int32_t res;
        uint32_t oct[4] = {0};
        const char *ip = "10.120.14.187";

        res = sscanf(ip, "%u.%u.%u.%u", &oct[0], &oct[1], &oct[2], &oct[3]);
        if ((res != ARR_SIZE(oct)) || (strlen(ip) > 15))
                goto end;

        while (res--) {
                if (oct[res] < 255)
                        continue;

                fprintf(stderr, "Error: Octet[%d]: %u\n", res, oct[res]);
                break;
        }

end:
        printf("%d\n", res);
        printf("%s IP is %s\n", ip, (res == -1) ? "valid" : "invalid");

        return !(res == -1);
}
