
#ifndef LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
#define LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H

void radix_sort(vector<vector<UI>> * vec, vector<vector<UI>> output, size_t n){
    for (UI i=0; i<4; i++){
        UI count[256] = {0};
        UI k = i * 8;
        for (UI j = 0; j < n; j++)
        {
            count[static_cast<uint8_t>(((*vec)[j][2] & (0xff << k)) >> k )]++;
        }

        for (UI j = 1; j < 256; j++)
            count[j] += count[j - 1];

        for (UI j = n; j > 0; j--)
        {
            uint8_t a = static_cast<uint8_t>(((*vec)[j-1][2] & (0xff << k)) >> k );
            output[count[a] - 1][0] = (*vec)[j-1][0];
            output[count[a] - 1][1] = (*vec)[j-1][1];
            output[count[a] - 1][2] = (*vec)[j-1][2];
            count[a]--;
        }

        for (UI j = 0; j < n; j++) {
            (*vec)[j][0] = output[j][0];
            (*vec)[j][1] = output[j][1];
            (*vec)[j][2] = output[j][2];
        }
    }
}

void bucketSort(vector<int> * vec, size_t n)
{
    // 1) Create n empty buckets
    vector<int> b[n];

    // 2) Put array elements in different buckets
    for (int i=0; i<n; i++)
    {
        int bi = n*((*vec)[i]/2147483647); // Index in bucket
        b[bi].push_back((*vec)[i]);
    }

    // 3) Sort individual buckets
    for (int i=0; i<n; i++)
        sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            (*vec)[index++] = b[i][j];
}

#endif //LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
