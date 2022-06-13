import express from 'express'
import child_process from 'child_process'
import path from 'path'
import dotenv from 'dotenv'

dotenv.config()
const app = express()
const execFile = child_process.execFile
app.use(express.static(path.join(path.resolve(), 'public')))

app.get('/simulation', (req, res) => {
    execFile(path.resolve(path.resolve(), 'a.out'))
    console.log(path.resolve(path.resolve(), 'a.out'))
})

app.get('*', (req, res) => {
    res.sendFile(path.join(path.resolve(), 'index.html'))
})

app.listen(process.env.PORT, console.log(`listening on port ${process.env.PORT}...`))