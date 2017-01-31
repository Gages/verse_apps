--[[
    This file is a work around for issue
    https://github.com/gittup/tup/issues/103
    The intended use of this file is that
    one specifies a set of environment variables with
    default values, and the script produces
    a tup configuration file with the current values of those
    variables, or a default value if they are not set,
    or returns with an error if the value is marked
    as mandatory.

    The purpose of this file is to make it easier to
    do cross platform builds in a parallel build environment
    (i.e the CI system can spawn multiple VMs, each
    with a different environment, rather than one VM
    with several tup variants).
]]

--[[
    The table "vars" is a dictionary where the keys
    are the name of the environment variable, and the key
    is the default value (a string).

    The resulting variable in tup will be an environment
    variable "CONFIG_%key", with key subsituted and with case
    preserved.


    The value "true" marks the var as being mandatory without a default value.
]]

function create_config(vars)

--[[
    The script reads in an output file name in the first parameter argument.
    If it isn't set it writes to stdout.
    An error opening the file causes an error to be thrown.
]]

local outfile = (function(filename)
    if filename then
        return io.open(filename, 'w')
    else
        return io.output()
    end
end)(arg[1])

local function write_var(name, value)
    outfile:write(string.format("CONFIG_%s=%s\n", name, value))
end

do
    for name, default in pairs(vars) do
        local value = os.getenv(name)
        if value == nil then
            if default == true then
                error(string.format("Mandatory envvar %s was not set.", name))
            else
                write_var(name, tostring(default))
            end
        else
          write_var(name, value)
        end
    end
end

outfile:close()

end --function create_config
