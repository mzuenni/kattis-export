#include "validation.h"
#include <numeric>
using namespace std;

int main(int argc, char *argv[]) {
    std::ifstream in(argv[1]);
    std::ifstream ans(argv[2]);
    OutputValidator team(argc, argv);

    int n,k,q;
    vector<int> T1, T2;
    in >> n >> k >> q;
    for(int i = 0; i < q; i++){
        int ni, t1, t2;
        in >> ni >> t1 >> t2;
        T1.push_back(t1);
        T2.push_back(t2);
    }

    string jury_ans; 
    ans >> jury_ans;
    for(auto& c : jury_ans) c = tolower(c);

    string team_ans = team.read_string("ans", 1, max(q, 10));
    team.newline();
    for(auto& c : team_ans) c = tolower(c);

    if(team_ans == "impossible"){
        if(jury_ans == "impossible"){
            team.eof_and_AC();
        }
        else{
            team.WA("Team said impossible but solution existed");
        }
    }

    if(team_ans.length() != q){
        team.WA("Incorrect length of output");
    }

    vector<pair<int,int>> events;
    vector<int> diff, keydiff;

    for(int i = 0; i < q; i++){
        if(team_ans[i] != '0' && team_ans[i] != '1'){
            team.WA("Invalid character printed");
        }
        int key_change = (team_ans[i] == '1');
        events.push_back({T1[i], events.size()});
        keydiff.push_back(-key_change);
        diff.push_back(-1);

        events.push_back({T2[i], events.size()});
        keydiff.push_back(key_change);
        diff.push_back(1);
    }

    sort(events.begin(), events.end());

    int keys = k;
    int people_indoors = n;

    for(int i = 0; i < events.size(); i++){
        int j = events[i].second;
        keys += keydiff[j];
        
        if(diff[j] == 1 && people_indoors == 0){
            bool has_key = (keydiff[j] != 0);
            if(!has_key){
                team.WA("A person came back without a key but nobody was home");
            }
        }

        people_indoors += diff[j];

        if(keys < 0){
            team.WA("Took too many keys");
        }
    }

    assert(jury_ans != "impossible");

    team.eof_and_AC();

}
