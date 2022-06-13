import express from 'express'
import child_process from 'child_process'
import path from 'path'
import dotenv from 'dotenv'
import { readSync } from 'fs'

dotenv.config()
const app = express()
const execFile = child_process.execFile
app.use(express.static(path.join(path.resolve(), 'public')))

app.get('/simulation', (req, res) => {
    execFile(path.resolve(path.resolve(), 'a.out'), [], (error, stdout, stderr) => {
        if(error) {
            res.send(error)
            return
        }
        if(stderr) {
            res.send(stderr)
            return
        }

        res.send(stdout)
    })
})

app.get('*', (req, res) => {
    res.sendFile(path.join(path.resolve(), 'index.html'))
})

app.listen(process.env.PORT, console.log(`listening on port ${process.env.PORT}...`))