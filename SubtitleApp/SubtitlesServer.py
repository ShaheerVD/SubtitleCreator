import assemblyai as aai
import sys
import os

from dotenv import load_dotenv

# Load environment variables from .env file
load_dotenv()

# Function to create subtitles for a video file




def create_subtitles(video_file,output_file):
    # Load API key from environment variable
 api_key = os.getenv("ASSEMBLYAI_API_KEY")
    

 aai.settings.api_key = api_key

 #transcribe video file using assemblyai
 transcript = aai.Transcriber().transcribe(video_file)
 #export subtitles in SRT format
 subtitles = transcript.export_subtitles_srt()

  #save subtitles to file
 with open(output_file, 'w') as f:
        f.write(subtitles)



if __name__ == "__main__":
    print("Coming in")
    video_file = sys.argv[1]
    output_file = sys.argv[2]
    create_subtitles(video_file, output_file)
