
#ifndef LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
#define LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H

#define MAX_TYPE  4294967295

bool comp(vector<UI> a, vector<UI> b){
    return a[2] < b[2];
}

void radix_alg(vector<vector<UI>> &vec, vector<vector<UI>> output){
    UI n = vec.size();
    for (UI i=0; i<4; i++){
        UI count[256] = {0};
        UI k = i * 8;
        for (UI j = 0; j < n; j++)
        {
            count[static_cast<uint8_t>((vec[j][2] & (0xff << k)) >> k )]++;
        }

        for (UI j = 1; j < 256; j++)
            count[j] += count[j - 1];

        for (UI j = n; j > 0; j--)
        {
            uint8_t a = static_cast<uint8_t>((vec[j-1][2] & (0xff << k)) >> k );
            output[count[a] - 1][0] = vec[j-1][0];
            output[count[a] - 1][1] = vec[j-1][1];
            output[count[a] - 1][2] = vec[j-1][2];
            count[a]--;
        }

        for (UI j = 0; j < n; j++) {
            vec[j][0] = output[j][0];
            vec[j][1] = output[j][1];
            vec[j][2] = output[j][2];
        }
    }
}

void radix_sort(vector<vector<UI>> &vec){
    radix_alg(vec, vec);
}

void bucket_sort(vector<vector<UI>> &vec, const UI &numBuckets)
{
    UI minElement, maxElement = vec[0][0];
    vector<vector<vector<UI>>> buckets;
    for (UI i=0; i<numBuckets; i++){
        vector<vector<UI>> v;
        buckets.push_back(v);
    }
    for (UI i=0; i<vec.size(); i++){
        if(vec[i][2] < minElement) minElement = vec[i][2];
        if(vec[i][2] > maxElement) maxElement = vec[i][2];
    }
    UI range = maxElement - minElement + 1;
    double d = double(numBuckets) / range;
    for (UI i=0; i<vec.size(); i++){
        UI index = UI((vec[i][2]-minElement) * d);
        buckets[index].push_back(vec[i]);
    }
    for (UI i=0; i<numBuckets; i++){
        sort(buckets[i].begin(), buckets[i].end(), comp);
    }
    vec.clear();
    for (UI i=0; i<numBuckets; i++){
        for (UI j=0; j<buckets[i].size(); j++){
            vec.push_back(buckets[i][j]);
        }
    }
}

//
//void bucket_sort(vector<UI> * vec, size_t n)
//{
//    // 1) Create n empty buckets
//    vector<UI> b[n];
//
//    // 2) Put array elements in different buckets
//    for (UI i=0; i<n; i++)
//    {
//        UI bi = n*((*vec)[i]/2147483647); // Index in bucket
//        b[bi].push_back((*vec)[i]);
//    }
//
//    // 3) Sort individual buckets
//    for (UI i=0; i<n; i++)
//        sort(b[i].begin(), b[i].end());
//
//    // 4) Concatenate all buckets into arr[]
//    UI index = 0;
//    for (UI i = 0; i < n; i++)
//        for (UI j = 0; j < b[i].size(); j++)
//            (*vec)[index++] = b[i][j];
//}



#endif //LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
