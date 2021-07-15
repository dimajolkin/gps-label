
#pragma once

class Server
{
private:
    uint8_t power = 10;
    uint16_t memory = 0;

    int16_t availableMemory(uint16_t min, uint16_t max)
    {
        if (min == max - 1)
        {
            return min;
        }

        int16_t size = max;
        int16_t lastSize = size;
        byte *buf;
        while ((buf = (byte *)malloc(size)) == NULL)
        {
            lastSize = size;
            size -= (max - min) / 2;
        };

        free(buf);
        return availableMemory(size, lastSize);
    }

public:
    uint8_t getPowerPercent()
    {
        return power;
    }

    int16_t getAvailableMemory()
    {
        return memory;
    }

    void printMemoryInfo()
    {
        // allocate enough room for every thread's stack statistics
        int cnt = osThreadGetCount();
        mbed_stats_stack_t *stats = (mbed_stats_stack_t *)malloc(cnt * sizeof(mbed_stats_stack_t));

        cnt = mbed_stats_stack_get_each(stats, cnt);
        for (int i = 0; i < cnt; i++)
        {
            printf("Thread: 0x%lX, Stack size: %lu / %lu\r\n", stats[i].thread_id, stats[i].max_size, stats[i].reserved_size);
        }
        free(stats);

        // Grab the heap statistics
        mbed_stats_heap_t heap_stats;
        mbed_stats_heap_get(&heap_stats);
        printf("Heap size: %lu / %lu bytes\r\n", heap_stats.current_size, heap_stats.reserved_size);
    }

    void update()
    {
        memory++; //availableMemory(0, 10000);
        power = 10;
    }
};