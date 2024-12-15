influx remote create \
	--name cloud-db \
	--remote-url https://eu-central-1-1.aws.cloud2.influxdata.com \
	--remote-api-token S_ghct9y6D0eLqIj-cXu3fJ1rnPEd5-9OTLvqMKXBMWMro9IMhFRLoo8SEv_BqJfpGXZO7tzEa0aNFF94W3WNw== \
	--remote-org-id 5f839e673fe78bb5

influx replication create \
	--name local-to-cloud \
	--remote-id 0e1eaa16b2e9d000 \
	--local-bucket-id 161cc161c88ad7bc \
	--remote-bucket b12929acdb8017ca
