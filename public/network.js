setTimeout(function(){
	connection = (function(window){
		//Make XHR request to load balancer
		//Extract list of available IPs
		//Test list of available IPs
		//Decide on winning server
		//Return winning server

		return{
			location: 'local',
			ip: 'localhost',
			ssl: false,
			port: 443
		};
	})(window);
}, 2000);