local hash = KEYS[1]
local id = ARGV[1]

redis.call("sadd", "collisions", hash)
local count = redis.call("incr", "count:"..hash)

local new_string = hash.."_"..count

redis.call("hset", "idmap:"..new_string, "id", id)

return new_string
