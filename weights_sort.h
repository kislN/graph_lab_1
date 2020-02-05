
#ifndef LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
#define LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H

template <typename T>
bool comp(EDGE<T> a, EDGE<T> b){
    return a.weight < b.weight;
}

template <typename T>
void radix_alg(vector<EDGE<T>> &vec, vector<EDGE<T>> output){
    UI n = vec.size();
    unsigned char type_size = sizeof(T);
    for (UI i=0; i<type_size; i++){
        vector<UI> count(256);
        UI k = i * 8;
        for (UI j = 0; j < n; j++)
        {
            count[static_cast<uint8_t>((vec[j].weight & (0xff << k)) >> k )]++;
        }

        for (UI j = 1; j < 256; j++)
            count[j] += count[j - 1];

        for (UI j = n; j > 0; j--)
        {
            uint8_t a = static_cast<uint8_t>((vec[j-1].weight & (0xff << k)) >> k );
            output[count[a] - 1].edge_a = vec[j-1].edge_a;
            output[count[a] - 1].edge_b = vec[j-1].edge_b;
            output[count[a] - 1].weight = vec[j-1].weight;
            count[a]--;
        }

        for (UI j = 0; j < n; j++) {
            vec[j].edge_a = output[j].edge_a;
            vec[j].edge_b = output[j].edge_b;
            vec[j].weight = output[j].weight;
        }
    }
}

template <typename T>
void radix_sort(vector<EDGE<T>> &vec){
    radix_alg(vec, vec);
}


template <typename T>
void bucket_sort(vector<EDGE<T>> &vec, const UI &num_buckets)
{
    T min_element = vec[0].weight, max_element = vec[0].weight;
    vector<vector<EDGE<T>>> buckets(num_buckets, vector<EDGE<T>>());

    for (UI i=0; i<vec.size(); i++){
        min_element = min(vec[i].weight, min_element);
        max_element = max(vec[i].weight, max_element);
    }

    T range = max_element - min_element + 1;
    double d = double(num_buckets) / range;

    for (UI i=0; i<vec.size(); i++){
        UI index = UI((vec[i].weight - min_element) * d);
        if (index == num_buckets) index--;
//        UI index = UI((vec[i].weight - min_element)/range);

        buckets[index].push_back(vec[i]);
    }
    for (UI i=0; i < num_buckets; i++){
        sort(buckets[i].begin(), buckets[i].end(), comp<T>);
    }

    vec.clear();

    for (UI i=0; i < num_buckets; i++){
        for (UI j=0; j<buckets[i].size(); j++){
            vec.push_back(buckets[i][j]);
        }
    }
}

//vector<UI> buck_sort_rec(vector<UI> &vec, UI min_element, UI max_element, UI n_buck){
//
//    if (vec.size()<2 || min_element==max_element){
//        return vec;
//    }
//    vector<vector<UI>> buckets(n_buck, vector<UI>());
//    UI range = max_element - min_element + 1;
//    for (UI i=0; i<vec.size(), i++){
//        UI index = UI((vec[i].weight - min_element) * d);
//        buckets[index].push_back(vec[i]);
//    }
//}

//double[] bucketSort (double[] array, double minElement, double maxElement)
//if array.length < 2 or minElement == maxElement
//return array;
//range = maxElement - minElement
//for i = 0  to array.length - 1
//index = int(array[i] * numBuckets / range)
//добавим array[i] в конец buckets[index]
//minBucktes[index] = minimum(buckets[index], array[i])
//maxBuckets[index] = maximum(buckets[index], array[i])
//for i = 0 to numBuckets - 1
//buckets[i] = bucketSort(buckets[i], minBucktes[i], maxBuckets[i])
//for i = 0 to numBuckets - 1
//for k = 0 to buckets[i].length - 1
//добавим buckets[i][k] в конец answer
//return answer


//void bucket_sort2(vector<UI> * vec, size_t n)
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
