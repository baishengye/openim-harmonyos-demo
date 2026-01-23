/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2024-2024. All rights reserved.
 */

import { hilog } from '@kit.PerformanceAnalysisKit';

const TAG = '[imsdk]'

class Logger {
  private domain: number;
  private prefix: string;
  private format: string = '%{public}s';

  constructor(prefix: string) {
    this.prefix = prefix;
    this.domain = 0xFF00;
  }

  /**
   * Outputs debug-level logs.
   * @param args Indicates the log parameters.
   */
  debug(message: string) {
    hilog.debug(this.domain, this.prefix, this.format, message);
  }

  /**
   * Outputs info-level logs.
   * @param args Indicates the log parameters.
   */
  info(message: string) {
    hilog.info(this.domain, this.prefix, this.format, message);
  }

  /**
   * Outputs warning-level logs.
   * @param args Indicates the log parameters.
   */
  warn(message: string) {
    hilog.warn(this.domain, this.prefix, this.format, message);
  }

  /**
   * Outputs error-level logs.
   * @param args Indicates the log parameters.
   */
  error(message: string) {
    hilog.error(this.domain, this.prefix, this.format, message);
  }
}

export default new Logger(TAG);