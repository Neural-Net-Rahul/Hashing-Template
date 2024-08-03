class HashedString{
	const ll M = 1e9+7;
	const ll B = 30;
	vector<ll>pow; // pow[0] = B^0 , pow[1] = B^1 .. pow[i] = B^i
	vector<ll>hash; // hash[i] = find the hash of string s[0..i]
	ll mod(ll a){
		return (a%M + M)%M;
	}
	ll mod_mul(ll a,ll b){
		return mod(mod(a)*mod(b));
	}
	ll mod_add(ll a,ll b){
		return mod(mod(a)+mod(b));
	}
public:
	HashedString(const string&s){
		ll n = s.size();
		pow.resize(n+2);
		hash.resize(n);
		hash[0] = s[0];
		for(ll i = 1;i<n;i++){
			hash[i] = mod_add(mod_mul(hash[i-1],B),s[i]);
		}
		pow[0] = 1;
		for(ll i = 1;i<=n+1;i++){
			pow[i] = mod_mul(pow[i-1],B);
		}
	}
	ll getHash(ll start,ll end){
		if(start==0){
			return mod(hash[end]);
		}
		return mod(hash[end]-mod_mul(hash[start-1],pow[end-start+1]));
	}
};
