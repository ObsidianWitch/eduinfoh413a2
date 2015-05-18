#!/usr/bin/lua

-- Paths
exe = "../out/tabu"
outDirectory = "out"
instancesDirectory = "instances"

-- Parameters
mRange = {4,4} -- FIXME
oRange = {2,2} -- FIXME
tRange = {4,4} -- FIXME
rRange = {4,4} -- FIXME

nParameters = 4
nConfigurations = (mRange[2] - mRange[1]  + 1)
    * (oRange[2] - oRange[1]  + 1)
    * (tRange[2] - tRange[1]  + 1)
    * (rRange[2] - rRange[1]  + 1)

function range(tRange)
    step = tRange[3] or 1
    return function(_, lastvalue)
        local nextvalue = lastvalue + step
        if step > 0 and nextvalue <= tRange[2] or step < 0 and
            nextvalue >= tRange[2] or step == 0
        then
            return nextvalue
        end
    end, nil, tRange[1] - step
end

--[[
 Retrieve instances which will be used for the tabu search.
--]]
function retrieveInstances()
    local instances = io.popen('ls ' .. instancesDirectory)
    local tInstances = {}
    local nInstances = 0
    
    for instance in instances:lines() do
        nInstances = nInstances + 1
        table.insert(tInstances, instance)
    end
    
    return tInstances, nInstances
end
instances, nInstances = retrieveInstances()

scriptProgression = 0
--[[
 Update and give the current progress of the script.
--]]
function scriptProgress()
    scriptProgression = scriptProgression + 1
    
    local total = nInstances * nConfigurations
    print("[" .. scriptProgression .. "/" .. total .. "]")
end

--[[
 Execute a tabu search on the specified instance, with the given parameters.
 Write the output to the specified resultFile.
--]]
function computeTabuInstance(instance, m, o, t, r, resultFile)
    scriptProgress()

    local tabuCmd = exe
        .. " -m " .. m
        .. " -o " .. o
        .. " -t " .. t
        .. " -r " .. r
        .. " -f " .. instancesDirectory .. "/" .. instance
    print(tabuCmd .. "\n")
    
    local tabuOut = io.popen(tabuCmd)
    extractWriteData(tabuOut, {m, o, t, r}, resultFile)
end

--[[
 Execute a tabu search on the specified instance with all the possible
 parameter configurations
--]]
function computeTabuInstanceAllConfigurations(instance)
    local resultFile = io.open(outDirectory .. "/" .. instance, "a")
    
    for m in range(mRange) do
        for o in range(oRange) do
            for t in range(tRange) do
                for r in range(rRange) do
                    computeTabuInstance(instance, m, o, t, r, resultFile)
                end
            end
        end
    end
    
    resultFile:close()
end

--[[
 Execute a tabu search on all instances and all configurations.
--]]
function computeTabuAll()
    for k, i in pairs(instances) do
        computeTabuInstanceAllConfigurations(i)
    end
end

--[[
 Extract data from the output of the tabu search program, and write it to the
 instance's result file.
--]]
function extractWriteData(tabuOut, parameters, resultFile)
    local finalScore, bestKnownScore, delta

    for line in tabuOut:lines() do
        if finalScore == nil then
            finalScore = line:match("final solution %(score: (%d+)")
        end
        
        if bestKnownScore == nil then
            bestKnownScore = line:match("best known score: (%d+)")
        end
    end

    delta = 100 * (bestKnownScore - finalScore)/bestKnownScore
    
    for k,p in pairs(parameters) do
        resultFile:write(p .. " ")
    end
    
    resultFile:write(finalScore .. " " .. bestKnownScore .. " ".. delta .. "\n")
end

-- Main
os.execute("mkdir -p " .. outDirectory)
computeTabuAll()
