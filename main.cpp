#include <iostream>
#include <vector>
using namespace std;
//插入排序
void SInsertSort(vector<int> &L); //直接选择排序
void BInsertSort(vector<int> &L); //折半选择排序
void ShellSort(vector<int> &L);   //希尔排序
//选择排序
void SelectSort(vector<int> &L, int n); //简单选择排序
void HeapSort(vector<int> &L);          //堆排序
//交换排序
void BubbleSort(vector<int> &L); //冒泡排序
void QuickSort(vector<int> &L); //快速排序
//归并排序
void MergeSort(vector<int> &L); //二路归并排序
int main()
{
    int a[8] = {49, 39, 65, 97, 76, 13, 27, 69};
    //通过数组a的地址初始化，注意地址是从0到8（左闭右开区间）
    vector<int> nums(a, a + 8);
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl
         << "Sorting..." << endl;
    //SInsertSort(nums);
    //BInsertSort(nums);
    //ShellSort(nums);
    //SelectSort(nums,7);
    //HeapSort(nums);
    //BubbleSort(nums);
    //QuickSort(nums);
    MergeSort(nums);
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
    return 0;
}
///////////////////////////////////////////////////////插入排序////////////////////////////////////////////////////////////////
// 直接插入排序
void SInsertSort(vector<int> &L)
{
    for (int i = 1; i < L.size(); i++)
    {
        int currentNumber = L[i];
        int j = i - 1;
        // 依次后挪
        while (j >= 0 && currentNumber < L[j])
        {
            L[j + 1] = L[j];
            j--;
        }
        // 插入当前待排序元素
        L[j + 1] = currentNumber;
    }
}

//折半插入排序
void BInsertSort(vector<int> &L)
{
    int low, high, mid;
    for (int i = 1; i < L.size(); i++)
    {
        int currentNumber = L[i];
        low = 0;
        high = i - 1;
        while (low <= high)
        {
            mid = low + (high - low) / 2; //折半
            if (currentNumber < L[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (int j = i - 1; j >= low; j--)
        {
            L[j + 1] = L[j];
        }
        L[low] = currentNumber;
    }
}

//希尔排序
void ShellSort(vector<int> &L)
{
    // 间隔序列，在希尔排序中我们称之为增量序列(希尔增量序列)
    for (int gap = L.size() / 2; gap > 0; gap /= 2)
    {
        // 分组
        for (int groupStartIndex = 0; groupStartIndex < gap; groupStartIndex++)
        {
            // 插入排序
            for (int currentIndex = groupStartIndex + gap; currentIndex < L.size(); currentIndex += gap)
            {
                // currentNumber 站起来，开始找位置
                int currentNumber = L[currentIndex];
                int preIndex = currentIndex - gap;
                while (preIndex >= groupStartIndex && currentNumber < L[preIndex])
                {
                    // 向后挪位置
                    L[preIndex + gap] = L[preIndex];
                    preIndex -= gap;
                }
                // currentNumber 找到了自己的位置，坐下
                L[preIndex + gap] = currentNumber;
            }
        }
    }
}
///////////////////////////////////////////////////////选择排序////////////////////////////////////////////////////////////////
//交换元素
void exchange(vector<int> &L, int i, int j)
{
    int tmp = L[i];
    L[i] = L[j];
    L[j] = tmp;
}

//简单选择排序
void SelectSort(vector<int> &L, int n)
{
    for (int i = 0; i < n; i++)
    {
        int minindex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (L[j] < L[minindex])
            {
                minindex = j;
            }
        }
        //交换
        exchange(L, i, minindex);
    }
}

//堆排序
/////////////////////////////子函数/////////////////////////////////

//调整大顶堆，第三个参数表示尚未排序元素的数量，即剩余堆的大小
void maxHeapify(vector<int> &L, int i, int heapsize)
{
    // 左、右子结点下标
    int left = 2 * i + 1;
    int right = left + 1;
    // 记录根结点、左子树结点、右子树结点三者中的最大值下标
    int largest = i;
    //与左子树比较
    if (left < heapsize && L[left] > L[largest])
        largest = left;
    //与右子树比较
    if (right < heapsize && L[right] > L[largest])
        largest = right;
    if (largest != i)
    {
        //将最大值与跟结点交换
        exchange(L, i, largest);
        //再次调整交换数字后的大顶堆
        maxHeapify(L, largest, heapsize);
    }
}
void buildMaxHeap(vector<int> &L)
{
    //从最后一个非叶子结点开始调整大顶堆，最后一个非叶子结点下标为L.size()/2-1
    for (int i = L.size() / 2 - 1; i >= 0; i--)
    {
        maxHeapify(L, i, L.size());
    }
}
/////////////////////////////主函数/////////////////////////////////
void HeapSort(vector<int> &L)
{
    //构建初始大顶堆
    buildMaxHeap(L);
    for (int i = L.size() - 1; i > 0; i--)
    {
        //将最大值放在数组最后
        exchange(L, 0, i);
        //调整剩余数组，使其满足大顶堆
        maxHeapify(L, 0, i);
    }
}

///////////////////////////////////////////////////////交换排序////////////////////////////////////////////////////////////////

//冒泡排序
void BubbleSort(vector<int> &L)
{
    bool swapped = true; //　初始置true以启动冒泡排序
    for (int i = 0; i < L.size() - 1; i++)
    {
        if (!swapped)
            break; //如上轮未发生交换，则说明剩余元素有序，无需再比较
        swapped = false;
        for (int j = 0; j < L.size() - 1 - i; j++)
        {
            if (L[j] > L[j + 1])
            {
                //未引入第三个临时变量即完成两个数字的交换
                L[j + 1] = L[j + 1] + L[j];
                L[j] = L[j + 1] - L[j];
                L[j + 1] = L[j + 1] - L[j];
                swapped = true; //交换元素置true
            }
        }
    }
}

//快速排序
/////////////////////////////子函数/////////////////////////////////
int partition(vector<int> &L, int low, int high)
{
    int pivot=L[low];
    int left=low+1;
    int right=high;
    while(left<right)
    {
        //找到右边第一个小于基数的位置
        while(left<right&&L[right]>=pivot) right--;
        //找到左边第一个大于基数的位置
        while(left<right&&L[left]<=pivot) left++;
        //交换这两个数，使得左边分区都小于等于基数，右边分区都大于等于基数
        if(left<right)
        {
            exchange(L,left,right);
            left++;
            right--;
        }
    }
    //分情形讨论：
    //左指针==右指针：需要判断该元素值是否大于基数，若大于，则新支点前移
    if(left==right&&L[right]>pivot) right--;
    //左指针>右指针：需要以小于基数的值和基数做交换（因为原基数在左边），因此以右指针为新支点，能保证左右分区all clear
    exchange(L,low,right);
    return right;
}
void quickSort(vector<int> &L, int low, int high)
{
    if (low < high)
    {
        //将数组分区，获取支点下标
        int mid = partition(L, low, high);
        //对左边区域快速排序
        quickSort(L, low, mid - 1);
        //对右边区域快速排序
        quickSort(L, mid + 1, high);
    }
}
/////////////////////////////主函数/////////////////////////////////
void QuickSort(vector<int> &L)
{
    quickSort(L, 0, L.size() - 1);
}

///////////////////////////////////////////////////////归并排序////////////////////////////////////////////////////////////////
//归并排序
/////////////////////////////子函数/////////////////////////////////
//将result的[start,middle]和[middle+1，end]合并
void Merge(vector<int> &L, int start, int end, vector<int> &result)
{
    int end1=(start+end)/2;
    int start2=end1+1;
    //用来遍历数组的指针
    int index1=start;
    int index2=start2;
    while(index1<=end1&&index2<=end)
    {
        if(L[index1]<=L[index2])
        {
            result[index1+index2-start2]=L[index1];
            index1++;
        }
        else
        {
            result[index1+index2-start2]=L[index2];
            index2++;
        }
    }
    //将剩余数字补在result后面
    while(index1<=end1)
    {
        result[index1+index2-start2]=L[index1];
        index1++;
    }
    while(index2<=end)
    {
        result[index1+index2-start2]=L[index2];
        index2++;
    }
    //将result操作区间的数字拷贝到L数组中，以便下次比较
    while(start<=end)
    {
        L[start]=result[start];
        start++;
    }
}
// 对L的[start,end]区间归并排序
void mergesort_st(vector<int> &L, int start,int end, vector<int> &result)
{
    //只剩下一个数字时，停止拆分
    if(start==end) return;
    int middle=(start+end)/2;
    //拆分出左边区域，将归并排序结果放在result[start,middle]中
    mergesort_st(L,start,middle,result);
    //拆分出右边区域，将归并排序结果放在result[middle+1,end]中
    mergesort_st(L,middle+1,end,result);
    //合并左右有序序列至result的[start,end]区间
    Merge(L,start,end,result);
}
/////////////////////////////主函数/////////////////////////////////
void MergeSort(vector<int> &L)
{
    if(L.size()==0) return;
    vector<int> result(L.size());
    mergesort_st(L,0,L.size()-1,result);
}