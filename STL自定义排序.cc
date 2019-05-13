写法一：(struct)
struct compare {
    bool operator()(const ListNode* a, const ListNode* b) {
        return a->val > b->val;
    }
};
priority_queue<ListNode*, vector<ListNode*>, compare> q;

struct Compare{
        bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
            return a.second <= b.first;
        }
};
set<pair<int, int>, Compare> s;

写法二：（lamda)
auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        };
priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> q(cmp);

写法三：（simpler lamda）
vector<vector<int>> courses；
sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
});
