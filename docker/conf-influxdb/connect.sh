influx remote create \
	--name cloud-db \
	--remote-url https://eu-central-1-1.aws.cloud2.influxdata.com \
	--remote-api-token MlOhaDEFRVN_fVrMVw_iMcyurl46fFNNB6N-K2Gj8FF3zR1JCyVesTrD9ntH7DYJthiWmzH9bHqbV9O1QVHKdg== \
	--remote-org-id 5f839e673fe78bb5

influx replication create \
	--name local-to-cloud \
	--remote-id 0e0842dce2fb7000 \
	--local-bucket-id 161cc161c88ad7bc \
	--remote-bucket b12929acdb8017ca
