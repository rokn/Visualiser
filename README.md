# Visualiser
The project for HackTUES

As of right now loops aren't supported, but a full program would look something like this:
EXAMPLES:

From:

![bubble_sort_image](https://github.com/rokn/Visualiser/blob/master/Examples/bubble_sort_example.jpg)

To:

'''objective-c
    int i, j, a, n, number[30];

    scanf("%d", &n);
    for (i = 0; i < n; ++i){
        scanf("%d", &number[i]);
    }
    for (i = 0; i < n; ++i){
        for (j = i + 1; j < n; ++j)
        {
            if (number[i] > number[j])
            {
                a =  number[i];
                number[i] = number[j];
                number[j] = a;
            }
        }
    }
'''