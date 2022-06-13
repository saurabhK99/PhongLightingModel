import express from 'express'
import child_process from 'child_process'
import path from 'path'

const app = express()
const execFile = child_process.execFile
app.use(express.static(path.join(path.resolve(), 'public')))

app.get('/simulation', (req, res) => {
    execFile('./a.out')
})

app.get('*', (req, res) => {
    res.sendFile(path.join(path.resolve(), 'index.html'))
})

app.listen(5001, console.log('listening on port 5001...'))